#ifndef PARSER_EXPRESSION_COMPARE_HPP_
#define PARSER_EXPRESSION_COMPARE_HPP_

#include "parser\expression\parser-expression.hpp"
#include "base\generic-constants.hpp"

//
// Base operator node
//
class ParserExpressionCompare : public ParserExpression {

public:
	ParserExpressionCompare (std::vector<ParserNode*>* arguments,
							 CompareOperators compare_op);

protected:
	// Override virtual functions from ParserNode
	ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk) { return NO_ERROR; }
	ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) { return NO_ERROR; }

	ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) { return NO_ERROR; }
	ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) { return NO_ERROR; }

	ErrorCode ConstantFoldPost (void) { return NO_ERROR; }

private:
	CompareOperators op_;
};

#endif // PARSER_EXPRESSION_COMPARE_HPP_