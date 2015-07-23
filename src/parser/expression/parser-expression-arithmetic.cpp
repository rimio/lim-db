#include "parser\expression\parser-expression-arithmetic.hpp"
#include <cassert>

ParserExpressionArithmetic::ParserExpressionArithmetic (
		std::vector<ParserNode*>* arguments,
		ArithmeticOperators arithmetic_op) {
	assert (arguments != NULL);
	assert (arguments->size () == 2);

	arguments_ = arguments;
	op_ = arithmetic_op;
}

