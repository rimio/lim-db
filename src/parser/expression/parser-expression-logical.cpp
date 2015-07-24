#include "parser\expression\parser-expression-logical.hpp"
#include <cassert>

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