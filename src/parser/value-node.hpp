#ifndef VALUE_NODE_HPP_
#define VALUE_NODE_HPP_

#include "parser/parser-node.hpp"

//
// Value node types
//
typedef enum
{
	PT_VALUE_INTEGER,
	PT_VALUE_FLOAT,
	PT_VALUE_STRING
} ValueType;

//
// Base class for all value nodes
//
class ValueNode : public TypedParserNode
{
private:
protected:
	// Hidden constructor
	ValueNode () { };

public:
	// Implementation of pure virtual functions
	virtual ParserNodeType getNodeType() const { return PT_VALUE; };
	virtual std::string print () { return ToString (); };

	// Returns the statement type
	virtual ValueType getValueType() const = 0;
};

//
// Integer value node
//
class IntegerValueNode : public ValueNode
{
private:
	// The actual value
	int value_;

protected:
	// Hidden default constructor
	IntegerValueNode () { };

public:
	// Constructors
	IntegerValueNode (int val) : value_ (val) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return std::to_string (value_); };
	virtual ValueType getValueType () const { return PT_VALUE_INTEGER; };
	virtual DataType getDataType () const { return DB_INTEGER; };

	// Getter for value
	int getValue () const { return value_; };
};

//
// Float value node
//
class FloatValueNode : public ValueNode
{
private:
	// The actual value
	float value_;

protected:
	// Hidden default constructor
	FloatValueNode () { };

public:
	// Constructors
	FloatValueNode (float val) : value_ (val) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return std::to_string (value_); };
	virtual ValueType getValueType () const { return PT_VALUE_FLOAT; };
	virtual DataType getDataType () const { return DB_FLOAT; };

	// Getter for value
	float getValue () const { return value_; };
};

//
// String value node
//
class StringValueNode : public ValueNode
{
private:
	// The actual value
	std::string value_;

protected:
	// Hidden default constructor
	StringValueNode () { };

public:
	// Constructors
	StringValueNode (std::string& val) : value_ (val) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "'" + value_ + "'"; };
	virtual ValueType getValueType () const { return PT_VALUE_STRING; };
	virtual DataType getDataType () const { return DB_STRING; };

	// Getter for value
	std::string getValue () const { return value_; };
};

#endif