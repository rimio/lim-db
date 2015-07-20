#include "parser-root.hpp"
#include "base\error-codes.hpp"

ErrorCode ParserRoot::Process () {
	ErrorCode error;

	// Compile phase
	error = Compile ();
	if (error != NO_ERROR) {
		return error;
	}

	// Prepare execution phase
	error = Prepare ();
	if (error != NO_ERROR) {
		return error;
	}

	// Execute
	return Execute ();
}