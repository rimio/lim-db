#ifndef DB_TYPE_HPP_
#define DB_TYPE_HPP_

//
// Data types
//
typedef enum
{
	DB_UNKNOWN,		// Not yet resolved
	DB_INTEGER,
	DB_FLOAT,
	DB_STRING,
	DB_BOOLEAN
} DataType;

#endif // DB_TYPE_HPP_