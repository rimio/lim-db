#ifndef PT_IDENTIFIER_HPP_
#define PT_IDENTIFIER_HPP_

#include "parser/parser-node.hpp"

//
// Base identifier node
//
class ParserIdentifier : public virtual ParserNode
{
public:

	std::string ToString () { return name_; };

	std::string name () { return name_; };
	void set_name (std::string name) { name_ = name; };

protected:
	// The identifier name
	std::string name_;

	// Hidden constructors
	ParserIdentifier () { };
	ParserIdentifier (std::string name) : name_ (name) { };

	// Override virtual functions from ParserNode
	ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode ConstantFoldPost (void) override { return NO_ERROR; }

	void GetChildren (std::vector<ParserNode *>* children) {};
};

#endif // PT_IDENTIFIER_HPP_