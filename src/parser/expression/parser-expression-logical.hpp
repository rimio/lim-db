#ifndef PARSER_EXPRESSION_LOGICAL_HPP_
#define PARSER_EXPRESSION_LOGICAL_HPP_

#include "parser\expression\parser-expression.hpp"
#include "base\generic-constants.hpp"

//
// Base operator node
//
class ParserExpressionLogical : public ParserExpression {

public:
	ParserExpressionLogical (std::vector<ParserNode*>* arguments,
							 LogicalOperators logical_op);

	LogicalOperators op() { return op_; }
protected:
	// Override virtual functions from ParserNode
	ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk);
	ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) { return NO_ERROR; }

	ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) { return NO_ERROR; }
	ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) { return NO_ERROR; }

	ErrorCode ConstantFoldPost ();

private:
	
	// Variables
	LogicalOperators op_;
};

#endif // PARSER_EXPRESSION_OR_HPP_