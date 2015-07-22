#include "storage\data-sector.hpp"

DataSector::DataSector(INT32 sector_id) {
	starting_pointer_ = GET_SECTOR_MANAGER()->GetSectorPointer(sector_id);
}

DataSector::~DataSector() {
	delete starting_pointer_;
}

BYTE* DataSector::Select() {
	return starting_pointer_;
}

BYTE* DataSector::Select(int row_number) {
	return starting_pointer_ + rows_.at(row_number);
}

