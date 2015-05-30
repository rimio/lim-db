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
	ER_SEMANTIC_ERROR,
	ER_PARSING_FAILED,
	ER_MISSING_PARSER_NODE,
	ER_INVALID_PARSER_NODE,
	ER_EXECUTION_FAILED,
	ER_LAST_ERROR
} ErrorCode;

//
// Error message format strings. 
//
static const std::string kErrorMessages[] = {
	"no error",
	"generic error",
	"syntax error, line %d column %d: %s",
	"semantic error, line %d column %d: %s",
	"parsing failed",
	"missing %s parser node",
	"invalid parser node",
	"execution failed"
};

#endif