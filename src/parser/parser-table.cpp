#include "parser\parser-table.hpp"
#include "boot\boot.hpp"

ParserTable::ParserTable () {
	table_ = NULL;
}

ParserTable::ParserTable (std::string name) {
	ParserTable ();
	STRING_TO_LOWER(name);
	name_ = name;
}

std::string ParserTable::ToString () {
	return name_;
}

ErrorCode ParserTable::NameResolvePre(NameResolveArg* arg, bool* stop_walk) {
	// Get the node on top and add Parser table to the node
	(*arg).tables_stack_.top().push_back(this);
	return NO_ERROR;
}

ErrorCode ParserTable::TypeCheckPre(TypeCheckArg* arg, bool* stop_walk) {
	std::vector <std::vector <DataType>> new_table;

	(*arg).tables_and_columns_stack_.top().push_back(new_table);

	return NO_ERROR;
}