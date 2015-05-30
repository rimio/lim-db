#ifndef PARSER_NODE_HPP_
#define PARSER_NODE_HPP_

#include "parser/location.hh"

//
// Parser node types
//
typedef enum
{
	PT_COMMAND,
	PT_STATEMENT
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

public:
	// Location getter/setter
	yy::location getLocation () const { return location_; }
	void setLocation (yy::location loc) { location_ = loc; }
	
	// Returns the type of parser node
	virtual ParserNodeType getNodeType () const = 0;
	
	// Returns a string representation of the node
	virtual std::string toString () = 0;
};

#endif