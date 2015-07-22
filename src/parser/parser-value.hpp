#ifndef PARSER_VALUE_HPP_
#define PARSER_VALUE_HPP_

#include "parser/parser-node.hpp"

//
// Base class for all value nodes
//
class ParserValue : public ParserNode {
protected:
	// Hidden constructor
	ParserValue () { };

	// Override virtual functions from ParserNode
	ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode ConstantFoldPost (void) override { return NO_ERROR; }

	void GetChildren (std::vector<ParserNode *>* children) {};
};

#endif // PARSER_VALUE_HPP_