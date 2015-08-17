#ifndef DB_TYPE_HPP_
#define DB_TYPE_HPP_

//
// Data types
//
typedef enum
{
	DB_UNKNOWN = -1,		// Not yet resolved

	DB_INTEGER = 0,
	DB_FLOAT,
	DB_STRING,
	DB_BOOLEAN,
	DB_MAX,

	DB_NUMERIC,		// integer, float
	DB_ANY,			// all types

	DB_ERROR        // uncomputable value       

} DataType;

DataType CommonType(DataType t1, DataType t2);
#endif // DB_TYPE_HPP_