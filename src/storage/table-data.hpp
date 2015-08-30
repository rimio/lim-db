#ifndef TABLE_DATA_HPP_
#define TABLE_DATA_HPP_

#include "base\error-codes.hpp"
#include "metadata\sector-group.hpp"

class TableData {
public:
	TableData(std::string t) { table_ = t;  sectors_ = new SectorGroup(); };
	~TableData() { delete sectors_; };
	SectorGroup* a_sectors() { return sectors_; };

	ErrorCode InsertIntoSector(BYTE *start, int length);

private:
	std::string table_;
	SectorGroup* sectors_;
};

#endif