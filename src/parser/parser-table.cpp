#include "parser\parser-table.hpp"

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