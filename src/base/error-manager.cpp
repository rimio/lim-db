#include "error-manager.hpp"
#include "error-codes.hpp"
#include <iostream>
#include <cstring>
#include <cassert>

void ErrorManager::reportError (const char *file, const int line, ErrorCode ercode, va_list& valist)
{
	char buffer[2048];

	// Check error code
	assert (ercode >= 0);
	assert (ercode < ER_LAST_ERROR);

	// Format string
    vsprintf (buffer, kErrorMessages[ercode].c_str (), valist);

	// Show error on standard error
	std::cerr << "[E" << (int) ercode << " @ " << file << ":" << line << "] " << buffer << std::endl;
}

ErrorCode ErrorManager::error (const char *file, const int line, ErrorCode ercode, ...)
{
	va_list argptr;
	
	// Check error code
	assert (ercode >= 0);
	assert (ercode < ER_LAST_ERROR);

	// Print error
	va_start (argptr, ercode);
	reportError (file, line, ercode, argptr);
	va_end (argptr);
	
	// Return received error code
	return ercode;
}

ErrorCode ErrorManager::syntaxError (const char *file, const int line, int row, int col, const std::string& message)
{
	return ErrorManager::error (file, line, ER_SYNTAX_ERROR, row, col, message.c_str ());
}

ErrorCode ErrorManager::semanticError (const char *file, const int line, int row, int col, const std::string& message)
{
	return ErrorManager::error (file, line, ER_SEMANTIC_ERROR, row, col, message.c_str ());
}