#ifndef PARSER_COMMAND_HPP_
#define PARSER_COMMAND_HPP_

#include "parser/parser-root.hpp"

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
class ParserCommand : public virtual ParserRoot {
public:
	ParserCommand (CommandType type) : type_ (type) {};

	std::string Print ();

protected:
	ErrorCode Compile () { return NO_ERROR; };
	ErrorCode Prepare () { return NO_ERROR; };
	ErrorCode Execute ();

private:
	ParserCommand ();

	CommandType type_;
};

#endif // PARSER_COMMAND_HPP_