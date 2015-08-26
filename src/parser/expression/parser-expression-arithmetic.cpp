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

ErrorCode ParserExpressionArithmetic::ConstantFoldPost() {
	ErrorCode er = NO_ERROR;

	// Get arguments
	std::vector<ParserNode*> children;
	this->GetChildren(&children);

	auto *left_child = children.at(0);
	auto *right_child = children.at(1);

	DatabaseValue result = DatabaseValue();
	
	// If at least one of the children is NULL, then the result is a NULL value
	if (left_child->computed_value().is_null() || right_child->computed_value().is_null()) {
		this->computed_value().set_is_null();
		return er;
	}

	switch (this->op()) {
	case PLUS:
		result = left_child->computed_value() + right_child->computed_value();
		break;
	case MINUS:
		result = left_child->computed_value() - right_child->computed_value();
		break;
	case MULTIPLY:
		result = left_child->computed_value() * right_child->computed_value();
		break;
	case DIVIDE:
		result = left_child->computed_value() / right_child->computed_value();
		break;
	case MODULO:
		if (left_child->computed_value().get_type()!= DB_INTEGER || right_child->computed_value().get_type() != DB_INTEGER)
			return ErrorManager::error(__HERE__, ER_ARITHMETIC_COMPUTATION, "MOD", "NON_INT", "NON_INT");
		result = left_child->computed_value() % right_child->computed_value();
		break;
	default:
		assert(false);
		return ER_FAILED;
		break;
	}

	if (result.get_type() == DB_ERROR)
		return ER_FAILED;

	this->set_computed_value(result);

	if (this->computed_value().get_type() != this->ExpectedType()){
		auto aux = this->computed_value();
		er = aux.Cast(this->ExpectedType());
		if (er != NO_ERROR)
			return er;
		this->set_computed_value(aux);
	}
	return er;
}