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
	bool left_is_null = false;
	bool right_is_null = false;
	DatabaseValue null_result = DatabaseValue();
	// Get arguments
	std::vector<ParserNode*> children;
	this->GetChildren(&children);

	// Extract the child(ren)
	bool rhs;
	bool lhs;
	auto left_child = children.at(0);
	if (left_child->computed_value().is_null())
		left_is_null = true;
	else
		lhs = left_child->computed_value().bool_value();

	// NOT is an unary expression
	if (this->op() != NOT) {
		auto right_child = children.at(1);
		if (right_child->computed_value().is_null())
			right_is_null = true;
		else
			rhs = right_child->computed_value().bool_value();
	}

	switch (this->op()) {
	case AND:
		if (right_is_null && left_is_null) {
			this->set_computed_value(null_result);
			return NO_ERROR;
		} else if (left_is_null) {
			if (rhs)
				this->set_computed_value(null_result);
			else
				this->set_computed_value(DatabaseValue(false));
			return NO_ERROR;
		} else if (right_is_null) {
			if (lhs)
				this->set_computed_value(null_result);
			else
				this->set_computed_value(DatabaseValue(false));
			return NO_ERROR;
		}
		else {
			if (rhs && lhs)
				this->set_computed_value(DatabaseValue(true));
			else
				this->set_computed_value(DatabaseValue(false));
		}
		break;
	case OR:
		if (right_is_null && left_is_null) {
			this->set_computed_value(null_result);
			return NO_ERROR;
		}
		else if (left_is_null) {
			if (rhs)
				this->set_computed_value(DatabaseValue(true));
			else
				this->set_computed_value(null_result);
			return NO_ERROR;
		}
		else if (right_is_null) {
			if (lhs)
				this->set_computed_value(DatabaseValue(true));
			else
				this->set_computed_value(null_result);
			return NO_ERROR;
		}
		else {
			if (rhs || lhs)
				this->set_computed_value(DatabaseValue(true));
			else
				this->set_computed_value(DatabaseValue(false));
		}
		break;
	case NOT:
		if (left_is_null) {
			this->set_computed_value(null_result);
			return NO_ERROR;
		} else
		if (lhs)
			this->set_computed_value(DatabaseValue(false));
		else
			this->set_computed_value(DatabaseValue(true));
		break;
	default:
		assert(false);
		return ER_FAILED;
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