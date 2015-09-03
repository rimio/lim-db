#ifndef TABLE_DATA_HPP_
#define TABLE_DATA_HPP_

#include "base\error-codes.hpp"
#include "metadata\sector-group.hpp"

class TableData {
public:
	TableData () { allocated_sectors_ = new SectorGroup(); };
	~TableData () { delete allocated_sectors_; };
	
	ErrorCode InsertIntoSector (BYTE *start, int length);	
	ErrorCode RetrieveFromSector (SectorID* last_sector_used, BYTE* last_row_used, BYTE **start, bool *has_next);
private:
	SectorGroup* allocated_sectors_;
};

#endif