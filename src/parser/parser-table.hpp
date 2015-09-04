#ifndef PARSER_TABLE_HPP_
#define PARSER_TABLE_HPP_

#include "base\generic-operations.hpp"
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
	Table* table () { return table_; }
	std::vector<DatabaseValue>* active_row() { return active_row_; }
	
	void set_name (std::string name) { STRING_TO_LOWER(name); name_ = name; };
	void set_table (Table *t) { table_ = t; };
	void set_active_row(std::vector<DatabaseValue> *row) { active_row_ = row; }

protected:

	// Override virtual functions from ParserNode
	ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) override;
	ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode ConstantFoldPost (void) override { return NO_ERROR; }

	void GetChildren (std::vector<ParserNode *>* children) {};

private:
	ParserTable ();

	// Members
	std::string name_;
	std::vector<DatabaseValue> *active_row_;

	// Future implementation
	std::string alias_;
	Table* table_;
};
#endif // PARSER_TABLE_HPP_