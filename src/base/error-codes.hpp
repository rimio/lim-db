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

	ER_OUT_OF_MEMORY,
	ER_ALLOCATION_TABLE_FULL,
	ER_SECTOR_OUT_OF_RANGE,
	ER_SECTOR_NOT_USED,
	ER_TABLE_ALREADY_EXISTS,
	ER_SAME_ATTRIBUTE,
	ER_TABLE_DOES_NOT_EXIST,
	ER_ALLOCATION_DATASECTOR_FULL,
	ER_INVALID_VALUE,
	ER_INEXISTENT_COLUMN,
	ER_INCONSISTENT_TUPLE,
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
	"execution failed",
	"out of memory: failed to allocate %d bytes",
	"out of memory: can't allocate sector. Table full",
	"can't deallocate sector with %d sectorID: out of range. "
	"Sector range: [ 0 %d ]",
	"can't deallocate sector with %d sectorID: currently not used",
	"a table with the name %s already exists",
	"attribute with the name %s is duplicated",
	"Can not find table with the name %s. There is no such table",
	"Can not serialize the row. Datasector is full.",
	"Value %s is not a propper one.",
	"There is no column %s in table %s",
	"The number of values in the tuple is inconsistent with the number of columns",
};

#endif