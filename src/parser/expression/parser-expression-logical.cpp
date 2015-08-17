#include "parser\expression\parser-expression-logical.hpp"

#include <cassert>

#include "metadata\database-value.hpp"
#include "parser\parser-value.hpp"

ParserExpressionLogical::ParserExpressionLogical (
		std::vector<ParserNode*>* arguments,
		LogicalOperators logical_op) {
	assert (arguments != NULL);
	assert ((logical_op == NOT && arguments->size () == 1)
			|| ((logical_op == AND || logical_op == OR)
				&& arguments->size () == 2));

	arguments_ = arguments;
	op_ = logical_op;
}

ErrorCode ParserExpressionLogical::TypeCheckPre(TypeCheckArg* arg, bool* stop_walk) {
	for (auto arg : *(this->arguments())) {
		arg->set_expected_type(DB_BOOLEAN);
	}
	return NO_ERROR;
}

ErrorCode ParserExpressionLogical::ConstantFoldPost() {
	ErrorCode er = NO_ERROR;

	// Get arguments
	std::vector<ParserNode*> children;
	this->GetChildren(&children);

	// Extract the child(ren)
	bool rhs;
	auto left_child = children.at(0);
	bool lhs = left_child->computed_value().bool_value();

	// NOT is an unary expression
	if (this->op() != NOT) {
		auto right_child = children.at(1);
		rhs = right_child->computed_value().bool_value();
	}

	switch (this->op()) {
	case AND:
		if (rhs && lhs)
			this->set_computed_value(DatabaseValue(true));
		else
			this->set_computed_value(DatabaseValue(false));
		break;
	case OR:
		if (rhs || lhs)
			this->set_computed_value(DatabaseValue(true));
		else
			this->set_computed_value(DatabaseValue(false));
		break;
	case NOT:
		if (lhs)
			this->set_computed_value(DatabaseValue(false));
		else
			this->set_computed_value(DatabaseValue(true));
		break;
	default:
		assert(false);
		return ER_FAILED;
		break;
	}

	// Convert to the expected type
	if (this->computed_value().get_type() != this->ExpectedType()){
		auto aux = this->computed_value();
		er = aux.Cast(this->ExpectedType());
		if (er != NO_ERROR)
			return er;
		this->set_computed_value(aux);
	}

	return er;
}