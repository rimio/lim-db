#ifndef ERROR_CODES_HPP_
#define ERROR_CODES_HPP_

#include <string>
#include <tuple>

//
// Error codes
//
typedef enum
{
	NO_ERROR = 0,
	ER_FAILED,
	ER_SYNTAX_ERROR,
	ER_LAST_ERROR
} ErrorCode;

//
// Error message format strings. Tuple is composed of:
//   (a) Number of arguments
//   (b) Format string
//
// Example: <1, "cannot allocate %d bytes">
//
static const std::tuple <int, std::string> kErrorMessages[] = {
	std::make_tuple (0, "no error"),
	std::make_tuple (0, "generic error"),
	std::make_tuple (2, "syntax error, line %d column %d: %s")
}

#endif