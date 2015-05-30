#ifndef ERROR_MANAGER_HPP_
#define ERROR_MANAGER_HPP_

#include "error-codes.hpp"

#include <string>
#include <stdarg.h>

//
// Errors handling routines gathered in a static class
//
class Error
{
private:
	// Common call point for all error routines
	static void reportError (ErrorCode ercode, const char *file, const int line, ...);

public:
	// Report a generic error
	static void error (const std::string error);

	// Report an internal error (unexpected behavior by the compiler)
	static void internalError (const std::string error);

	// Report a syntax error in the code
	static void syntaxError (const std::string error, int line, int column);

	// Report a semantic error in the code
	static void semanticError (const std::string error, ParserNode *node);
};

#endif