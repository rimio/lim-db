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
class OperatorNode : public ParserNode
{
private:
	// Inaccessible default constructor
	OperatorNode () { };

protected:
	// Left/right part of expression

public:
	// Implementation of pure virtual functions
};

// ---------------------------- Logical Operators --------------------------- //
class OrOperatorNode : public OperatorNode
{
private:
protected:
public:
};

class AndOperatorNode : public OperatorNode
{
private:
protected:
public:
};

class NotOperatorNode : public OperatorNode
{
private:
protected:
public:
};

// -------------------------- Comparison operators -------------------------- //
class LtOperatorNode : public OperatorNode
{
private:
protected:
public:
};

class LtEqOperatorNode : public OperatorNode
{
private:
protected:
public:
};

class GtOperatorNode : public OperatorNode
{
private:
protected:
public:
};

class GtEqOperatorNode : public OperatorNode
{
private:
protected:
public:
};

class EqualOperatorNode : public OperatorNode
{
private:
protected:
public:
};

class NotEqualOperatorNode : public OperatorNode
{
private:
protected:
public:
};

// -------------------------- Arithmetic operators -------------------------- //
class PlusOperatorNode : public OperatorNode
{
private:
protected:
public:
};

class MinusOperatorNode : public OperatorNode
{
private:
protected:
public:
};

class MultiplicationOperatorNode : public OperatorNode
{
private:
protected:
public:
};

class DivisionOperatorNode : public OperatorNode
{
private:
protected:
public:
};

class ModuloOperatorNode : public OperatorNode
{
private:
protected:
public:
};

#endif