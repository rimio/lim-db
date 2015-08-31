#ifndef TABLE_DATA_HPP_
#define TABLE_DATA_HPP_

#include "base\error-codes.hpp"
#include "metadata\sector-group.hpp"

class TableData {
public:
	TableData (std::string t) { allocated_sectors_ = new SectorGroup(); };
	~TableData () { delete allocated_sectors_; };
	
	ErrorCode InsertIntoSector (BYTE *start, int length);	
private:
	SectorGroup* allocated_sectors_;
};

#endif