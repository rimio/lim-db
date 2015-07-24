#include "storage\data-sector.hpp"

DataSector::~DataSector() {
	delete slots_;
}

BYTE* DataSector::Select() {
	return get_data() + SECTOR_MAX_SIZE - slots_[num_rows_].offset;
}

BYTE* DataSector::Select(int row_number) {
	return get_data() + SECTOR_MAX_SIZE - slots_[row_number].offset;
}

ErrorCode DataSector::Insert(BYTE *ptr, int length_required) {
	int alligned_length_required = ((length_required - 1) / 4 + 1) * 4;
	
	BYTE *last_used = get_data() + SECTOR_MAX_SIZE;
	if (num_rows_ != 0) {
		last_used -= slots_[num_rows_ - 1].offset;
	}

	// Create a new slot
	Slot new_slot;
	new_slot.length = length_required;
	new_slot.offset = get_data() + SECTOR_MAX_SIZE - last_used + alligned_length_required;
	
	BYTE *start = get_data();

	// Check if there is enough space for the serialized row and its offset
	if ((start + (num_rows_+1)*SLOT_SIZE) < (last_used - alligned_length_required)) {
		
		// Serialize the new slot
		memcpy(start + num_rows_*SLOT_SIZE, &new_slot.offset, sizeof(new_slot.offset));
		memcpy(start + num_rows_*SLOT_SIZE+2, &new_slot.length, sizeof(new_slot.length));
		
		slots_[num_rows_] = new_slot;
		++num_rows_;

		start = last_used - alligned_length_required;

		// Store the new serialized row
		memcpy(start, ptr, length_required);
	}
	else {
		// TODO should try to defragmentate the DataSector in order to find space 
		return ErrorManager::error(__HERE__, ER_ALLOCATION_DATASECTOR_FULL);
	}
	
	return NO_ERROR;
}

void DataSector::UseDataSector(DataSector *sector, int meta_data_size) {
	sector->UseSector(sector, meta_data_size);
	num_rows_ = 0;
}