#ifndef ERROR_MANAGER_HPP_
#define ERROR_MANAGER_HPP_

#include "error-codes.hpp"

#include <string>
#include <cstring>
#include <cstdarg>

//
// Macro for the file-line combo
//
#if defined (_WIN32)
	#define __FILENAME__	(::strrchr(__FILE__, '\\') ? ::strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
	#define __FILENAME__	(::strrchr(__FILE__, '/') ? ::strrchr(__FILE__, '/') + 1 : __FILE__)
#endif
#define __HERE__		__FILENAME__, __LINE__

//
// Errors handling routines gathered in a static class
//
class ErrorManager
{
private:
	// Common call point for all error routines
	static void reportError (const char *file, const int line, ErrorCode ercode, va_list& valist);

public:
	// Report an error
	static ErrorCode error (const char *file, const int line, ErrorCode ercode, ...);
	
	// Report a syntax error
	static ErrorCode syntaxError (const char *file, const int line, int row, int col, const std::string& message);
	
	// Report a semantic error
	static ErrorCode semanticError (const char *file, const int line, int row, int col, const std::string& message);
};

#endif