#include "error-manager.hpp"
#include "error-codes.hpp"
#include <iostream>
#include <cstring>
#include <cassert>

static void reportError (ErrorCode ercode, const char *file, const int line, ...)
{
	char buffer[2048];
	va_list argptr;

	// Check error code
	assert (ercode >= 0);
	assert (ercode < ER_LAST_ERROR);

	// Format string
	va_start (argptr, std::get<0>(kErrorMessages[ercode]));
    vsprintf (buffer, std::get<1>(kErrorMessages[ercode]), argptr);
    va_end (argptr);

	// Show error on standard error
	std::cerr << "[E" << (int) ercode << "] " << buffer << std::endl;
}

void Error::error (const std::string error)
{
	Error::reportError ("Error: " + error);
}

void Error::internalError (const std::string error)
{
	Error::reportError ("Internal error: " + error);
}

void Error::syntaxError (const std::string error, int line, int column)
{
	Error::reportError ("Syntax error at line " + std::to_string (line) + " column " + std::to_string (column) + ": " + error);
}

void Error::semanticError (const std::string error, ParserNode *node)
{
	yy::location loc = node->getLocation ();

	Error::reportError ("Semantic error at line " + std::to_string (loc.begin.line)
						+ " column " + std::to_string (loc.begin.column) +  ": " + error);
}