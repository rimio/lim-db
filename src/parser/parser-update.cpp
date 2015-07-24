#include "parser\parser-update.hpp"
#include "base\generic-operations.hpp"

//
// PTInsertNode
//

ParserUpdate::~ParserUpdate () {
	// delete table node
	
}

std::string ParserUpdate::ToString () {
	return std::string("UPDATE");
}

//
// PTInsertRoot
//

ParserUpdateStatement::ParserUpdateStatement (yy::location loc) {
	setLocation (loc);
}

ErrorCode ParserUpdateStatement::Compile () {
	return NO_ERROR;
}

ErrorCode ParserUpdateStatement::Prepare () {
	return NO_ERROR;
}

ErrorCode ParserUpdateStatement::Execute () {
	return NO_ERROR;
}

std::string ParserUpdateStatement::Print () {
	return ToString ();
}