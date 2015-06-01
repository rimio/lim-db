#ifndef COMMAND_NODE_HPP_
#define COMMAND_NODE_HPP_

#include "parser/parser-node.hpp"

//
// Command types
//
typedef enum
{
	PT_COMMAND_EXIT
} CommandType;

//
// Base class for command node
//
class CommandNode : public ParserNode
{
private:
protected:
	// Hidden constructor
	CommandNode () { };

public:
	// Implementation of pure virtual functions
	virtual ParserNodeType getNodeType () const { return PT_COMMAND; };
	
	// Returns the command type
	virtual CommandType getCommandType () const = 0;
};

//
// Exit command node
//

class ExitCommandNode : public CommandNode
{
private:
protected:
public:
	// Implementation of pure virtual functions
	virtual std::string toString () { return "EXIT"; };
	virtual std::string print () { return "EXIT"; };
	virtual CommandType getCommandType () const { return PT_COMMAND_EXIT; };
};


#endif