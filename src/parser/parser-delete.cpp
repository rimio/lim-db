#include "parser\parser-delete.hpp"
#include "base\generic-operations.hpp"

//
// PTInsertNode
//

ParserDelete::~ParserDelete () {
	// delete table node
	
}

std::string ParserDelete::ToString () {
	return std::string("DELETE");
}

//
// PTInsertRoot
//

ParserDeleteStatement::ParserDeleteStatement (yy::location loc) {
	setLocation (loc);
}

ErrorCode ParserDeleteStatement::Compile () {
	return NO_ERROR;
}

ErrorCode ParserDeleteStatement::Prepare () {
	return NO_ERROR;
}

ErrorCode ParserDeleteStatement::Execute () {
	return NO_ERROR;
}

std::string ParserDeleteStatement::Print () {
	return ToString ();
}