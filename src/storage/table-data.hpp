#ifndef TABLE_DATA_HPP_
#define TABLE_DATA_HPP_

#include "base\error-codes.hpp"
#include "schema\table.hpp"
class TableData {
public:
	TableData(Table *t) { table_ = t;  };
	ErrorCode InsertIntoSector(BYTE *start, int length);
private:
	Table *table_;
};

#endif