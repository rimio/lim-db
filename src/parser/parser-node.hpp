#ifndef PARSER_NODE_HPP_
#define PARSER_NODE_HPP_

#include "parser/location.hh"
#include "base/data-type.hpp"

//
// Parser node types
//
typedef enum
{
	PT_COMMAND,
	PT_STATEMENT,
	PT_VALUE,
	PT_IDENTIFIER,
	PT_OPERATOR
} ParserNodeType;

//
// Base class for all parser nodes
//
class ParserNode
{
private:
protected:
	// Position in input buffer
	yy::location location_;

	// Next node in list
	ParserNode *next_;

	// Hidden constructor
	ParserNode ();

public:
	// Virtual destructor
	virtual ~ParserNode ();

	// Location getter/setter
	yy::location getLocation () const { return location_; }
	void setLocation (yy::location loc) { location_ = loc; }
	
	// Returns the type of parser node
	virtual ParserNodeType getNodeType () const = 0;
	
	// Returns a string representation of the node
	virtual std::string toString () = 0;

	// Returns a printable string representation of the node and it's children
	virtual std::string print () = 0;

	// Prints the node as a list, separated by a specified separator
	virtual std::string printList (std::string sep);

	// Specifies whether the parser node has an associated data type.
	// If this returns true, it may be cast to TypedParserNode to retireve
	// the data type.
	// NOTE: It is inferred that all typed nodes can evaluate to a value,
	// either at compile time or at runtime.
	virtual bool isTyped () const { return false; };

	// Getter and setter for reference to next node
	ParserNode *getNext () const { return next_; }
	void setNext (ParserNode *next) { next_ = next; }
};

//
// Base class for all typed parser nodes
//
class TypedParserNode : public virtual ParserNode
{
private:
protected:
	// Hidden constructor
	TypedParserNode () { };

public:
	// All derived node types have a data type
	virtual bool isTyped () const { return true; };

	// Returns the data type of the parser node
	virtual DataType getDataType () const = 0;
};

#endif