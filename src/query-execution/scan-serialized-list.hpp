#ifndef SCAN_SERIALIZED_LIST_HPP_
#define SCAN_SERIALIZED_LIST_HPP_

#include "query-execution\scan.hpp"
#include "storage\row-data.hpp"

class ScanSerializedList: Scan {
public:
	ScanSerializedList(Table* t) { table_ = t; }
	void Start() override;
	void End() override {};
	bool HasNext() override { return true; };
	ErrorCode Next(RowData* row, bool* has_next);
private:	
	Table* table_;
	SectorID last_sector_used_;
	BYTE last_row_used_;
};

#endif