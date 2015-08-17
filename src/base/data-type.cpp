#include "base\data-type.hpp"

DataType CommonType(DataType t1, DataType t2) {
	DataType result = DB_INTEGER;
	if (t1 == DB_FLOAT || t2 == DB_FLOAT)
		result = DB_FLOAT;
	if (t1 == DB_STRING || t2 == DB_STRING)
		result = DB_STRING;
	return result;
}