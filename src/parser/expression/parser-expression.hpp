#ifndef OPERATOR_NODE_HPP_
#define OPERATOR_NODE_HPP_

#include "parser/parser-node.hpp"

//
// Operator types
//
typedef enum
{
	PT_OPERATOR_OR,
	PT_OPERATOR_AND,
	PT_OPERATOR_NOT,

	PT_OPERATOR_LT,
	PT_OPERATOR_LT_EQ,
	PT_OPERATOR_GT,
	PT_OPERATOR_GT_EQ,
	PT_OPERATOR_EQUAL,
	PT_OPERATOR_NOT_EQUAL,

	PT_OPERATOR_PLUS,
	PT_OPERATOR_MINUS,
	PT_OPERATOR_MULTIPLICATION,
	PT_OPERATOR_DIVISION,
	PT_OPERATOR_MODULO
} OperatorType;

//
// Base operator node
//
class ParserExpression : public ParserNode {


protected:
	// Return type
	DataType return_type_;

	// Override virtual functions from ParserNode
	ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk) { return NO_ERROR; }
	ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) { return NO_ERROR; }

	virtual ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) { return NO_ERROR; }
	virtual ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) { return NO_ERROR; }

	virtual ErrorCode ConstantFoldPost (void) { return NO_ERROR; }

private:
	// Inaccessible default constructor
	ParserExpression () { };
};

#endif