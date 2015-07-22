#include "parser\parser-alter-table.hpp"

ParserAlterTableStatement::~ParserAlterTableStatement () {
}

std::string ParserAlterTableStatement::Print () {
	return std::string ("ALTER TABLE");
}

ErrorCode ParserAlterTableStatement::Compile () {
	return NO_ERROR;
}

ErrorCode ParserAlterTableStatement::Execute () {
	return NO_ERROR;
}