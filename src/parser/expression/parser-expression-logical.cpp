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
	set_expected_type(DB_BOOLEAN);
	
	return NO_ERROR;
}

ErrorCode ParserExpressionLogical::Compute(DataType expected_type, ParserNode* *value) {
	ErrorCode er = NO_ERROR;

	// Cast to a compare expression
	ParserExpressionLogical* exp = (ParserExpressionLogical*)(*value);

	// Get arguments
	std::vector<ParserNode*> children;
	((ParserExpression*)(exp))->GetChildren(&children);
	
	// Solve all arguments
	for (auto child = children.begin(); child != children.end(); child++) {
		er = (*child)->Compute(DB_BOOLEAN, &(*child));
		if (er != NO_ERROR)
			return er;
	}

	// Extract the child(ren)
	bool rhs;

	auto left_child = children.at(0);
	bool lhs = ((((ParserValue*)(left_child))->value()))->bool_value();

	// NOT is an unary expression
	if (exp->op() != NOT) {
		auto right_child = children.at(1);
		rhs = ((((ParserValue*)(right_child))->value()))->bool_value();
	}

	switch (exp->op()) {
	case AND:
		if (rhs && lhs)
			(*value) = new ParserValue(new DatabaseValue(true));
		else
			(*value) = new ParserValue(new DatabaseValue(false));
		break;
	case OR:
		if (rhs || lhs)
			(*value) = new ParserValue(new DatabaseValue(true));
		else
			(*value) = new ParserValue(new DatabaseValue(false));
		break;
	case NOT:
		if (lhs)
			(*value) = new ParserValue(new DatabaseValue(false));
		else
			(*value) = new ParserValue(new DatabaseValue(true));
		break;
	default:
		break;
	}

	// Convert to the expected type
	if (expected_type != DB_ANY) {
		DatabaseValue* val = ((ParserValue*)(*value))->value();
		er = exp->Convert(((ParserValue*)(*value))->value()->get_type(), expected_type, &val);
		if (er == NO_ERROR)
			((ParserValue*)(*value))->set_value(val);
	}

	delete exp;

	return er;
}