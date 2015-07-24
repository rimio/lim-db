#include "parser\expression\parser-expression-compare.hpp"
#include <cassert>

ParserExpressionCompare::ParserExpressionCompare (
		std::vector<ParserNode*>* arguments,
		CompareOperators compare_op) {
	assert (arguments != NULL);
	assert (arguments->size () == 2);

	arguments_ = arguments;
	op_ = compare_op;
}

