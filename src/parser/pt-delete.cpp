#include "parser\pt-delete.hpp"
#include "base\generic-operations.hpp"

//
// PTInsertNode
//

PTDeleteNode::~PTDeleteNode () {
	// delete table node
	
}

std::string PTDeleteNode::ToString () {
	return std::string("DELETE");
}

//
// PTInsertRoot
//

PTDeleteRoot::PTDeleteRoot (yy::location loc) {
	setLocation (loc);
}

ErrorCode PTDeleteRoot::Compile () {
	return NO_ERROR;
}

ErrorCode PTDeleteRoot::Prepare () {
	return NO_ERROR;
}

ErrorCode PTDeleteRoot::Execute () {
	return NO_ERROR;
}

std::string PTDeleteRoot::Print () {
	return ToString ();
}