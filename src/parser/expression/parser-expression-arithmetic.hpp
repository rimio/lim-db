#ifndef PARSER_EXPRESSION_ARITHMETIC_HPP_
#define PARSER_EXPRESSION_ARITHMETIC_HPP_

#include "parser\expression\parser-expression.hpp"
#include "base\generic-constants.hpp"
#include "parser\parser-node.hpp"
#include "base\data-type.hpp"
//
// Base operator node
//
class ParserExpressionArithmetic : public ParserExpression {

public:
	ParserExpressionArithmetic(std::vector<ParserNode*>* arguments,
		ArithmeticOperators arithmetic_op);

	ErrorCode Compute (DataType expected_type, ParserNode* *value) override;
	
	ArithmeticOperators op() { return op_; }
protected:
	// Override virtual functions from ParserNode
	ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk);
	ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) { return NO_ERROR; }

	ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) { return NO_ERROR; }
	ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) { return NO_ERROR; }

	ErrorCode ConstantFoldPost (void) { return NO_ERROR; }

private:
	ArithmeticOperators op_;
};

#endif // PARSER_EXPRESSION_ARITHMETIC_HPP_