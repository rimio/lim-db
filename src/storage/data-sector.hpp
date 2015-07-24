#ifndef DATA_SECTOR_HPP_
#define DATA_SECTOR_HPP_

#include "base\generic-constants.hpp"
#include "storage\sector.hpp"

#include <vector>

#define SLOT_SIZE 4

class DataSector: Sector {
	struct Slot {
		UINT16 offset;
		UINT16 length;
	};

public:
	~DataSector();
	//Row_number starts with 0
	BYTE* Select(int row_number);
	//Returns all rows contained
	std::vector<BYTE*> Select();
	//Inserts a row in the DataSector
	ErrorCode Insert(BYTE* ptr, int length_required);

	void UseDataSector(DataSector *sector);

private:
	INT16 num_rows_;
	UINT16 offset_to_last_row_data_;
	Slot slots_[1];
};

#endif