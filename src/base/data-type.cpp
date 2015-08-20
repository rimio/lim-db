#include "base\data-type.hpp"

DataType CommonType(DataType t1, DataType t2) {
	DataType result = DB_INTEGER;
	
	if (t1 == DB_STRING || t2 == DB_STRING) {
		result = DB_STRING;
	} else if (t1 == DB_FLOAT || t2 == DB_FLOAT) {
		result = DB_FLOAT;
	} else if (t1 == DB_BOOLEAN && t2 == DB_BOOLEAN) {
		result = DB_BOOLEAN;
	}

	if ((t1 == DB_BOOLEAN && t2 != DB_BOOLEAN) || (t2 == DB_BOOLEAN && t1 != DB_BOOLEAN))
		result = DB_ERROR;
	
	return result;
}