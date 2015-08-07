#include "parser\expression\parser-expression-compare.hpp"

#include <cassert>

#include "metadata\database-value.hpp"
#include "parser\parser-value.hpp"

#define MACHINE_ERROR 0.0000001

ParserExpressionCompare::ParserExpressionCompare (
		std::vector<ParserNode*>* arguments,
		CompareOperators compare_op) {
	assert (arguments != NULL);
	assert (arguments->size () == 2);

	arguments_ = arguments;
	op_ = compare_op;
}

ErrorCode ParserExpressionCompare::TypeCheckPre(TypeCheckArg* arg, bool* stop_walk) {
	set_expected_type(DB_BOOLEAN);
	
	return NO_ERROR;
}

ErrorCode ParserExpressionCompare::Compute(DataType expected_type, ParserNode* *value) {
	ErrorCode er = NO_ERROR;

	// Cast to a compare expression
	ParserExpressionCompare* exp = (ParserExpressionCompare*)(*value);

	// Get arguments
	std::vector<ParserNode*> children;
	((ParserExpression*)(exp))->GetChildren(&children);

	// Solve all arguments
	for (auto child = children.begin(); child != children.end(); child++) {
		er = (*child)->Compute(DB_ANY, &(*child));
		if (er != NO_ERROR)
			return er;
	}
	
	// Extract the children
	auto left_child = children.at(0);
	auto right_child = children.at(1);

	// Decide what is the DataType of the comparison made
	DataType comparison;

	switch (left_child->ExpectedType()){
	case DB_INTEGER:
		comparison = DB_INTEGER;
		break;
	case DB_FLOAT:
		comparison = DB_FLOAT;
		break;
	case DB_STRING:
		comparison = DB_STRING;
		break;
	case DB_BOOLEAN:
		comparison = DB_BOOLEAN;
		break;
	default:
		// Case of DB_NUMERIC
		comparison = DB_FLOAT;
		break;
	}

	switch (comparison) {
	case DB_INTEGER:
		if (right_child->ExpectedType() == DB_FLOAT || right_child->ExpectedType() == DB_STRING)
		comparison = DB_FLOAT;
		break;
	case DB_STRING:
		if (right_child->ExpectedType() == DB_INTEGER || right_child->ExpectedType() == DB_FLOAT)
		comparison = DB_FLOAT;
		break;
	case DB_BOOLEAN:
		if (right_child->ExpectedType() == DB_INTEGER) comparison= DB_INTEGER;
		if (right_child->ExpectedType() == DB_FLOAT) comparison = DB_FLOAT;
		if (right_child->ExpectedType() == DB_STRING) comparison = DB_STRING;
		if (right_child->ExpectedType() == DB_BOOLEAN) comparison = DB_INTEGER;
		break;
	default:
		// Case of  DB_NUMERIC
		comparison = DB_FLOAT;
		break;
	}

	// Convert the children to the same type
	if (left_child->ExpectedType() != comparison) {
		er = (left_child)->Compute(comparison, &left_child);
		if (er != NO_ERROR)
			return er;
	}

	if (right_child->ExpectedType() != comparison) {
		er = (right_child)->Compute(comparison, &right_child);
		if (er != NO_ERROR)
			return er;
	}

	// result = 1 if left > right
	// result = 0 if left = right
	// result = -1 if left < right
	int result;

	switch (comparison) {
	case DB_INTEGER:
		if (((((ParserValue*)(left_child))->value()))->int_value() > ((((ParserValue*)(right_child))->value()))->int_value())
			result = 1;
		else 
			if (((((ParserValue*)(left_child))->value()))->int_value() == ((((ParserValue*)(right_child))->value()))->int_value())
				result = 0;
			else result = -1;
		break;
	case DB_FLOAT:
		if (fabs(((((ParserValue*)(left_child))->value()))->float_value() - ((((ParserValue*)(right_child))->value()))->float_value()) < MACHINE_ERROR)
			result = 0;
		else 
			if (((((ParserValue*)(left_child))->value()))->float_value() > ((((ParserValue*)(right_child))->value()))->float_value())
				result = 1;
			else
				result = -1;
		break;
	case DB_STRING:
		if (((((ParserValue*)(left_child))->value()))->string_value() > ((((ParserValue*)(right_child))->value()))->string_value())
			result = 1;
		else
			if (((((ParserValue*)(left_child))->value()))->string_value() == ((((ParserValue*)(right_child))->value()))->string_value())
				result = 0;
			else result = -1;
		break;
	default:
		break;
	}

	switch (exp->op()) {
	case EQ:
		if (result == 0) 
			(*value) = new ParserValue(new DatabaseValue(true));
		else
			(*value) = new ParserValue(new DatabaseValue(false));
		break;
	case NOT_EQ:
		if (result == 0)
			(*value) = new ParserValue(new DatabaseValue(false));
		else
			(*value) = new ParserValue(new DatabaseValue(true));
		break;
	case LT:
		if (result == -1)
			(*value) = new ParserValue(new DatabaseValue(true));
		else
			(*value) = new ParserValue(new DatabaseValue(false));
		break;
	case LT_EQ:
		if (result == 1)
			(*value) = new ParserValue(new DatabaseValue(false));
		else
			(*value) = new ParserValue(new DatabaseValue(true));
		break;
	case GT:
		if (result == 1)
			(*value) = new ParserValue(new DatabaseValue(true));
		else
			(*value) = new ParserValue(new DatabaseValue(false));
		break;
	case GT_EQ:
		if (result == -1)
			(*value) = new ParserValue(new DatabaseValue(false));
		else
			(*value) = new ParserValue(new DatabaseValue(true));
		break;
	default:
		break;
	}
	
	// Convert the result to the expected type
	if (expected_type != DB_ANY) {
		DatabaseValue* val = ((ParserValue*)(*value))->value();
		er = exp->Convert(((ParserValue*)(*value))->value()->get_type(), expected_type, &val);
		if (er == NO_ERROR)
			((ParserValue*)(*value))->set_value(val);
	}

	delete exp;

	return er;
}