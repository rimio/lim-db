#include "parser\expression\parser-expression-arithmetic.hpp"
#include "parser\parser-value.hpp"
#include "metadata\database-value.hpp"
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
	for (auto arg : *(this->arguments())) {
		arg->set_expected_type(DB_NUMERIC);
	}
	return NO_ERROR;
}

/*
ErrorCode ParserExpressionArithmetic::Compute (DataType expected_type, ParserNode* *value) {
	ErrorCode er = NO_ERROR;
	
	// Cast to an aritmetic expression
	ParserExpressionArithmetic* exp = (ParserExpressionArithmetic*)(*value);

	// Need for the corectness of DIV, MOD expressions
	if (expected_type == DB_INTEGER)
		exp->set_expected_type(DB_INTEGER);

	// Get arguments
	std::vector<ParserNode*> children;
//	((ParserExpression*)(exp))->GetChildren(&children);

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
	DatabaseValue* db_val;

	switch (dominant_type) {
	case DB_INTEGER:
		iresult = ((((ParserValue*)(children.at(0)))->value()))->int_value();
		switch (exp->op()) {
		case PLUS:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				iresult += (((ParserValue*)(*child))->value())->int_value();
			}
			break;
		case MINUS:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				iresult -= (((ParserValue*)(*child))->value())->int_value();
			}
			break;
		case MULTIPLY:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				iresult *= (((ParserValue*)(*child))->value())->int_value();
			}
			break;
		case DIVIDE:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				iresult /= (((ParserValue*)(*child))->value())->int_value();
			}
			break;
		case MODULO:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				iresult %= (((ParserValue*)(*child))->value())->int_value();
			}
			break;
		default:
			break;
		}

		db_val = new DatabaseValue(iresult);
		(*value) = new ParserValue(db_val);
		break;
	case DB_FLOAT:
		fresult = (((ParserValue*)(children.at(0)))->value())->float_value();
		switch (exp->op()) {
		case PLUS:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				fresult += (((ParserValue*)(*child))->value())->float_value();
			}
			break;
		case MINUS:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				fresult -= (((ParserValue*)(*child))->value())->float_value();
			}
			break;
		case MULTIPLY:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				fresult *= (((ParserValue*)(*child))->value())->float_value();
			}
			break;
		case DIVIDE:
			for (auto child = children.begin() + 1; child != children.end(); child++) {
				fresult /= (((ParserValue*)(*child))->value())->float_value();
			}
			break;
		case MODULO:
			return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);
			break;
		default:
			break;
		}

		db_val = new DatabaseValue(fresult);
		(*value) = new ParserValue(db_val);
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
*/

ErrorCode ParserExpressionArithmetic::ConstantFoldPost() {
	ErrorCode er = NO_ERROR;

	// Get arguments
	std::vector<ParserNode*> children;
	this->GetChildren(&children);
	
	auto *left_child = children.at(0);
	auto *right_child = children.at(1);

	
	// Holds which is the broadest type of the result
	DataType dominant_type = (left_child->computed_value().get_type() == DB_INTEGER 
			                 && right_child->computed_value().get_type() == DB_INTEGER) ? DB_INTEGER : DB_FLOAT;

	if (left_child->computed_value().get_type() != dominant_type) {
		auto aux = left_child->computed_value();
		er = aux.Cast(dominant_type);
		if (er != NO_ERROR)
			return er;
		left_child->set_computed_value(aux);
	}

	if (right_child->computed_value().get_type() != dominant_type) {
		auto aux = right_child->computed_value();
		er = aux.Cast(dominant_type);
		if (er != NO_ERROR)
			return er;
		right_child->set_computed_value(aux);
	}
	
	// Compute the result
	// Whatever the operator between numbers, we can consider a plus sign in front of the first one
	INT32 iresult;
	float fresult;
	DatabaseValue* db_val;

	switch (dominant_type) {
	case DB_INTEGER:
		iresult = (left_child->computed_value()).int_value();
		switch (this->op()) {
		case PLUS:
			iresult += (right_child->computed_value()).int_value();
			break;
		case MINUS:
			iresult -= (right_child->computed_value()).int_value();
			break;
		case MULTIPLY:
			iresult *= (right_child->computed_value()).int_value();
			break;
		case DIVIDE:
			iresult /= (right_child->computed_value()).int_value();
			break;
		case MODULO:
			iresult %= (right_child->computed_value()).int_value();
			break;
		default:
			break;
		}

		this->set_computed_value((*(new DatabaseValue(iresult))));
		break;
	case DB_FLOAT:
		fresult = (left_child->computed_value()).float_value();
		switch (this->op()) {
		case PLUS:
			fresult += (right_child->computed_value()).float_value();
			break;
		case MINUS:
			fresult -= (right_child->computed_value()).float_value();
			break;
		case MULTIPLY:
			fresult *= (right_child->computed_value()).float_value();
			break;
		case DIVIDE:
			fresult /= (right_child->computed_value()).float_value();
			break;
		case MODULO:
			return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);
			break;
		default:
			break;
		}

		this->set_computed_value((*(new DatabaseValue(fresult))));
		break;
	default:
		break;
	}

	if (this->computed_value().get_type() != this->ExpectedType()){
		auto aux = this->computed_value();
		er = aux.Cast(this->ExpectedType());
		if (er != NO_ERROR)
			return er;
		this->set_computed_value(aux);
	}
	return er;
}