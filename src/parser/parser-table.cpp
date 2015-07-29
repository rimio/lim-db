#include "parser\parser-table.hpp"
#include "boot\boot.hpp"

ParserTable::ParserTable () {
	table_ = NULL;
}

ParserTable::ParserTable (std::string name) {
	ParserTable ();

	name_ = name;
}

std::string ParserTable::ToString () {
	return name_;
}

ErrorCode ParserTable::NameResolvePre(NameResolveArg* arg, bool* stop_walk) {
	// Get the node on top
	std::vector <ParserTable *> last_node =  (*arg).tables_stack_.top();

	// Create a new Parser Table
	ParserTable *pt = new ParserTable(table_->get_table_name());
	pt->table_ = GET_SCHEMA_MANAGER()->FindTable(table_->get_table_name());

	// Add Parser table to the node
	last_node.push_back(pt);
	
	return NO_ERROR;
}