#ifndef PARSER_INDEX_HPP_
#define PARSER_INDEX_HPP_

#include "parser\parser-node.hpp"
#include "schema\table.hpp"

// Parse-tree node containing data about a database table
class ParserIndex : public virtual ParserNode {
public:
	ParserIndex (std::string name);

	std::string ToString ();

	// Accessors
	// TODO: Is it better to use pointers/references?
	std::string name () { return name_; };
	void set_name (std::string name) { name_ = name; };

	ErrorCode Compute(DataType expected_type_, ParserNode* *value) override { return NO_ERROR; };
protected:
	// Override virtual functions from ParserNode
	ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode ConstantFoldPost (void) override { return NO_ERROR; }

	void GetChildren (std::vector<ParserNode *>* children) {};

private:
	ParserIndex ();

	// Members
	std::string name_;

	// Future implementation
	Table* table_;
};
#endif // PARSER_INDEX_HPP_