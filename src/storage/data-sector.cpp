#include "storage\data-sector.hpp"

DataSector::~DataSector() {
	delete starting_pointer_;
	free(slots_);
}

BYTE* DataSector::Select() {
	return starting_pointer_;
}

BYTE* DataSector::Select(int row_number) {
	return starting_pointer_ + slots_[row_number].offset;
}

