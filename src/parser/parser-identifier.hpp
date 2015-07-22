#ifndef PT_IDENTIFIER_HPP_
#define PT_IDENTIFIER_HPP_

#include "parser/parser-node.hpp"

//
// Base identifier node
//
class ParserIdentifier : public virtual ParserNode
{
private:
protected:
	// The identifier name
	std::string name_;

	// Hidden constructors
	ParserIdentifier () { };
	ParserIdentifier (std::string name) : name_ (name) { };

public:

	std::string ToString () { return name_; };

	std::string name () { return name_; };
	void set_name (std::string name) { name_ = name; };
};

#endif // PT_IDENTIFIER_HPP_