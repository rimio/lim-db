#ifndef PT_COMMAND_HPP_
#define PT_COMMAND_HPP_

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
class PTCommand : public virtual ParserRoot {
public:
	PTCommand (CommandType type) : type_ (type) {};

	std::string Print ();

protected:
	ErrorCode Compile () { return NO_ERROR; };
	ErrorCode Prepare () { return NO_ERROR; };
	ErrorCode Execute ();

private:
	PTCommand ();

	CommandType type_;
};

#endif // PT_COMMAND_HPP_