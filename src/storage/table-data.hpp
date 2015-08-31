#ifndef TABLE_DATA_HPP_
#define TABLE_DATA_HPP_

#include "base\error-codes.hpp"
#include "metadata\sector-group.hpp"

class TableData {
public:
	TableData(std::string t) { table_ = t;  sectors_ = new SectorGroup(); };
	~TableData() { delete sectors_; };

	void set_table_name(std::string name) { table_ = name; }
	SectorGroup* a_sectors() { return sectors_; };

	ErrorCode InsertIntoSector(BYTE *start, int length);
	
private:
	std::string table_;
	SectorGroup* sectors_;
};

#endif