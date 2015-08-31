#include "storage\data-sector.hpp"
#include "base\generic-operations.hpp"
#include <cassert>

DataSector::~DataSector() {
	delete slots_;
}

std::vector<BYTE*> DataSector::Select() {
	std::vector<BYTE*> result;

	for (int i = 0; i < num_rows_; i++) {
		UINT16 from_int16;
		memcpy(&from_int16, (BYTE *) &slots_[i], sizeof(from_int16));
		BYTE *ptr = ((BYTE*) this) + (int)(from_int16);
		result.push_back(ptr);
	}

	return result;
} 

BYTE* DataSector::Select(int row_number) {
	assert(row_number >= 0 && row_number < num_rows_);
	return ((BYTE *) this) + slots_[row_number].offset;
}

ErrorCode DataSector::Insert(BYTE *ptr, int length_required, bool *has_free_space) {
	*has_free_space = true;
	int data_size = ALIGN_SIZE (length_required, 4);
	int slot_and_data_size = data_size + sizeof(Slot);

	if (free_ < slot_and_data_size) {
		*has_free_space = false;
		return NO_ERROR;
	}
	
	UINT16 new_row_offset = offset_to_last_row_data_ - data_size;
	BYTE *new_row_data_ptr = ((BYTE *) this) + new_row_offset;
	assert (new_row_data_ptr > (BYTE *) &slots_[num_rows_ + 1]);

	// Copy row data
	memcpy(new_row_data_ptr, ptr, length_required);

	// Set slot for new row
	slots_[num_rows_].offset = new_row_offset;
	slots_[num_rows_].length = length_required;
	num_rows_++;
	
	offset_to_last_row_data_ = new_row_offset;

	return NO_ERROR;
}

void DataSector::UseDataSector(DataSector *sector) {
	self_ref_ = 0;
	type_ = SECTOR_DATA;
	max_contiguous_free_ = 0;
	dead_ = 0;
	deleted_ = 0;

	num_rows_ = 0;
	slots_[0].offset = 0;
	slots_[0].length = 0;

	free_ = SECTOR_MAX_SIZE - offsetof(DataSector, slots_);
	offset_to_last_row_data_ = SECTOR_MAX_SIZE;
}