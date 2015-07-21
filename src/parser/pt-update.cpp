#include "parser\pt-update.hpp"
#include "base\generic-operations.hpp"

//
// PTInsertNode
//

PTUpdateNode::~PTUpdateNode () {
	// delete table node
	
}

std::string PTUpdateNode::ToString () {
	return std::string("UPDATE");
}

//
// PTInsertRoot
//

PTUpdateRoot::PTUpdateRoot (yy::location loc) {
	setLocation (loc);
}

ErrorCode PTUpdateRoot::Compile () {
	return NO_ERROR;
}

ErrorCode PTUpdateRoot::Prepare () {
	return NO_ERROR;
}

ErrorCode PTUpdateRoot::Execute () {
	return NO_ERROR;
}

std::string PTUpdateRoot::Print () {
	return ToString ();
}