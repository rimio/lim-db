#include "parser\expression\parser-expression-arithmetic.hpp"
#include "parser\parser-value.hpp"

#include "metadata\database-value.hpp"
#include "metadata\int-database-value.hpp"
#include "metadata\float-database-value.hpp"
#include "metadata\bool-database-value.hpp"
#include "metadata\string-database-value.hpp"

#include "base\error-manager.hpp"
#include "base\error-codes.hpp"


#include <cassert>

ParserExpressionArithmetic::ParserExpressionArithmetic (
		std::vector<ParserNode*>* arguments,
		ArithmeticOperators arithmetic_op) {
	assert (arguments != NULL);
	assert (arguments->size () == 2);

	arguments_ = arguments;
	op_ = arithmetic_op;
}

ErrorCode ParserExpressionArithmetic::TypeCheckPre(TypeCheckArg* arg, bool* stop_walk) {
	// DB_FLOAT includes DB_INTEGER
	set_expected_type(DB_FLOAT);
	
	return NO_ERROR;
}


ErrorCode ParserExpressionArithmetic::Compute (DataType expected_type, ParserNode* *value) {
	ErrorCode er = NO_ERROR;
	
	// Cast to an aritmetic expression
	ParserExpressionArithmetic* exp = (ParserExpressionArithmetic*)(*value);

	// Need for the corectness of DIV, MOD expressions
	if (expected_type == DB_INTEGER)
		exp->set_expected_type(DB_INTEGER);

	// Get arguments
	std::vector<ParserNode*> children;
	((ParserExpression*)(exp))->GetChildren(&children);

	// Holds which is the broadest type of the result
	DataType dominant_type = DB_INTEGER;

	// Solve all arguments
	for (auto child = children.begin(); child != children.end(); child++) {
		er = (*child)->Compute(exp->ExpectedType(), &(*child));
		if (er != NO_ERROR)
			return er;
		if (((ParserValue*)(*child))->value()->get_type() == DB_FLOAT || ((ParserValue*)(*child))->value()->get_type() == DB_NUMERIC) 
			dominant_type = DB_FLOAT;	
	}

	// Convert all types of arguments to the broadest one
	for (auto child : children) {
		if (((ParserValue*)(child))->value()->get_type() != dominant_type) {
			DatabaseValue* val = ((ParserValue*)(child))->value();
			ErrorCode er = ((ParserNode*)(child))->Convert(((ParserValue*)(child))->value()->get_type(), dominant_type, &val);
			if (er == NO_ERROR)
				((ParserValue*)(child))->set_value(val);
			else
				return er;
		}
	}

	// Compute the result
	// Whatever the operator between numbers, we can consider a plus sign in front of the first one
	INT32 iresult;
	float fresult;
	FloatDatabaseValue* fl_db_val;
	IntDatabaseValue* int_db_val;

	switch (dominant_type) {
	case DB_INTEGER:
		iresult = ((IntDatabaseValue*)(((ParserValue*)(children.at(0)))->value()))->get_value();
		switch (exp->op()) {
		case PLUS:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				iresult += ((IntDatabaseValue*)(((ParserValue*)(*child))->value()))->get_value();
			}
			break;
		case MINUS:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				iresult -= ((IntDatabaseValue*)(((ParserValue*)(*child))->value()))->get_value();
			}
			break;
		case MULTIPLY:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				iresult *= ((IntDatabaseValue*)(((ParserValue*)(*child))->value()))->get_value();
			}
			break;
		case DIVIDE:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				iresult /= ((IntDatabaseValue*)(((ParserValue*)(*child))->value()))->get_value();
			}
			break;
		case MODULO:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				iresult %= ((IntDatabaseValue*)(((ParserValue*)(*child))->value()))->get_value();
			}
			break;
		default:
			break;
		}

		int_db_val = new IntDatabaseValue(iresult);
		(*value) = new ParserValue(int_db_val);
		break;
	case DB_FLOAT:
		fresult = ((FloatDatabaseValue*)(((ParserValue*)(children.at(0)))->value()))->get_value();
		switch (exp->op()) {
		case PLUS:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				fresult += ((FloatDatabaseValue*)(((ParserValue*)(*child))->value()))->get_value();
			}
			break;
		case MINUS:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				fresult -= ((FloatDatabaseValue*)(((ParserValue*)(*child))->value()))->get_value();
			}
			break;
		case MULTIPLY:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				fresult *= ((FloatDatabaseValue*)(((ParserValue*)(*child))->value()))->get_value();
			}
			break;
		case DIVIDE:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				fresult /= ((FloatDatabaseValue*)(((ParserValue*)(*child))->value()))->get_value();
			}
			break;
		case MODULO:
			return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);
			break;
		default:
			break;
		}

		fl_db_val = new FloatDatabaseValue(fresult);
		(*value) = new ParserValue(fl_db_val);
		break;
	default:
		break;
	}
	
	if (expected_type != DB_ANY) {
		DatabaseValue* val = ((ParserValue*)(*value))->value();
		er = exp->Convert(((ParserValue*)(*value))->value()->get_type(), expected_type, &val);
		if (er == NO_ERROR)
			((ParserValue*)(*value))->set_value(val);
	}
	
	delete exp;

	return er;
}
