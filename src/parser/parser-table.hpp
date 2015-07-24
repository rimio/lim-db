#ifndef PARSER_TABLE_HPP_
#define PARSER_TABLE_HPP_

#include "parser\parser-node.hpp"
#include "schema\table.hpp"

// Parse-tree node containing data about a database table
class ParserTable : public virtual ParserNode {
public:
	ParserTable (std::string name);

	std::string ToString ();

	// Accessors
	// TODO: Is it better to use pointers/references?
	std::string name () { return name_; };
	void set_name (std::string name) { name_ = name; };

protected:

	// Override virtual functions from ParserNode
	ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode ConstantFoldPost (void) override { return NO_ERROR; }

	void GetChildren (std::vector<ParserNode *>* children) {};

private:
	ParserTable ();

	// Members
	std::string name_;

	// Future implementation
	std::string alias_;
	Table* table_;
};
#endif // PARSER_TABLE_HPP_