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
class OperatorNode : public TypedParserNode
{
private:
	// Inaccessible default constructor
	OperatorNode () { };

protected:
	// Left/right part of expression
	TypedParserNode *left_;
	TypedParserNode *right_;

	// Return type
	DataType return_type_;

	// Hidden constructors
	OperatorNode (TypedParserNode *left) : left_ (left), right_ (nullptr), return_type_ (DB_UNKNOWN) { };
	OperatorNode (TypedParserNode *left, TypedParserNode *right) : left_ (left), right_ (right), return_type_ (DB_UNKNOWN) { };

public:
	// Implementation of pure virtual functions
	virtual ParserNodeType getNodeType () const { return PT_OPERATOR; };
	virtual DataType getDataType () const { return return_type_; };
	
	// Returns the statement type
	virtual OperatorType getOperatorType () const = 0;
};

// ---------------------------- Logical Operators --------------------------- //
class OrOperatorNode : public OperatorNode
{
private:
protected:
public:
	OrOperatorNode (TypedParserNode *left, TypedParserNode *right) : OperatorNode (left, right) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "OR"; };
	virtual OperatorType getOperatorType () const { return PT_OPERATOR_OR; };
	virtual DataType getDataType () const { return DB_BOOLEAN; };
};

class AndOperatorNode : public OperatorNode
{
private:
protected:
public:
	AndOperatorNode (TypedParserNode *left, TypedParserNode *right) : OperatorNode (left, right) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "AND"; };
	virtual OperatorType getOperatorType () const { return PT_OPERATOR_AND; };
	virtual DataType getDataType () const { return DB_BOOLEAN; };
};

class NotOperatorNode : public OperatorNode
{
private:
protected:
public:
	NotOperatorNode (TypedParserNode *left) : OperatorNode (left, nullptr) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "NOT"; };
	virtual OperatorType getOperatorType () const { return PT_OPERATOR_NOT; };
	virtual DataType getDataType () const { return DB_BOOLEAN; };
};

// -------------------------- Comparison operators -------------------------- //
class LtOperatorNode : public OperatorNode
{
private:
protected:
public:
	LtOperatorNode (TypedParserNode *left, TypedParserNode *right) : OperatorNode (left, right) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "<"; };
	virtual OperatorType getOperatorType () const { return PT_OPERATOR_LT; };
	virtual DataType getDataType () const { return DB_BOOLEAN; };
};

class LtEqOperatorNode : public OperatorNode
{
private:
protected:
public:
	LtEqOperatorNode (TypedParserNode *left, TypedParserNode *right) : OperatorNode (left, right) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "<="; };
	virtual OperatorType getOperatorType () const { return PT_OPERATOR_LT_EQ; };
	virtual DataType getDataType () const { return DB_BOOLEAN; };
};

class GtOperatorNode : public OperatorNode
{
private:
protected:
public:
	GtOperatorNode (TypedParserNode *left, TypedParserNode *right) : OperatorNode (left, right) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return ">"; };
	virtual OperatorType getOperatorType () const { return PT_OPERATOR_GT; };
	virtual DataType getDataType () const { return DB_BOOLEAN; };
};

class GtEqOperatorNode : public OperatorNode
{
private:
protected:
public:
	GtEqOperatorNode (TypedParserNode *left, TypedParserNode *right) : OperatorNode (left, right) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return ">="; };
	virtual OperatorType getOperatorType () const { return PT_OPERATOR_GT_EQ; };
	virtual DataType getDataType () const { return DB_BOOLEAN; };
};

class EqualOperatorNode : public OperatorNode
{
private:
protected:
public:
	EqualOperatorNode (TypedParserNode *left, TypedParserNode *right) : OperatorNode (left, right) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "="; };
	virtual OperatorType getOperatorType () const { return PT_OPERATOR_EQUAL; };
	virtual DataType getDataType () const { return DB_BOOLEAN; };
};

class NotEqualOperatorNode : public OperatorNode
{
private:
protected:
public:
	NotEqualOperatorNode (TypedParserNode *left, TypedParserNode *right) : OperatorNode (left, right) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "<>"; };
	virtual OperatorType getOperatorType () const { return PT_OPERATOR_NOT_EQUAL; };
	virtual DataType getDataType () const { return DB_BOOLEAN; };
};

// -------------------------- Arithmetic operators -------------------------- //
class PlusOperatorNode : public OperatorNode
{
private:
protected:
public:
	PlusOperatorNode (TypedParserNode *left, TypedParserNode *right) : OperatorNode (left, right) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "+"; };
	virtual OperatorType getOperatorType () const { return PT_OPERATOR_PLUS; };
};

class MinusOperatorNode : public OperatorNode
{
private:
protected:
public:
	MinusOperatorNode (TypedParserNode *left, TypedParserNode *right) : OperatorNode (left, right) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "-"; };
	virtual OperatorType getOperatorType () const { return PT_OPERATOR_MINUS; };
};

class MultiplicationOperatorNode : public OperatorNode
{
private:
protected:
public:
	MultiplicationOperatorNode (TypedParserNode *left, TypedParserNode *right) : OperatorNode (left, right) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "*"; };
	virtual OperatorType getOperatorType () const { return PT_OPERATOR_MULTIPLICATION; };
};

class DivisionOperatorNode : public OperatorNode
{
private:
protected:
public:
	DivisionOperatorNode (TypedParserNode *left, TypedParserNode *right) : OperatorNode (left, right) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "/"; };
	virtual OperatorType getOperatorType () const { return PT_OPERATOR_DIVISION; };
};

class ModuloOperatorNode : public OperatorNode
{
private:
protected:
public:
	ModuloOperatorNode (TypedParserNode *left, TypedParserNode *right) : OperatorNode (left, right) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "MOD"; };
	virtual OperatorType getOperatorType () const { return PT_OPERATOR_MODULO; };
};

#endif