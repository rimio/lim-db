#ifndef PARSER_VALUE_HPP_
#define PARSER_VALUE_HPP_

#include "parser/parser-node.hpp"
#include "metadata/database-value.hpp"

//
// Base class for all value nodes
//
class ParserValue : public ParserNode {
public:
	ParserValue(DatabaseValue* value) : value_(value) {};
	
	DatabaseValue* value() { return value_; };

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

	DatabaseValue *value_;
};

#endif // PARSER_VALUE_HPP_