#include "storage\sector-manager.hpp"

#include <cstdlib>

#define NUMBER_OF_SECTORS 10

SectorManager::SectorManager() {
	allocation_table_ = new Bitmap(NUMBER_OF_SECTORS, false);
	storage_pointer_ = (BYTE*)malloc(NUMBER_OF_SECTORS * SECTOR_MAX_SIZE);
	sector_size_ = SECTOR_MAX_SIZE;
	last_used_ = 0;
}

SectorManager::~SectorManager(){
	delete storage_pointer_;
	delete allocation_table_;
}

ErrorCode SectorManager::AllocateSector(SectorID * sector_id){
	//Starts to search for the desired empty space from the previous successful one
	(*sector_id) = (*allocation_table_).GiveFreeBit(last_used_);
	last_used_ = (*sector_id);

	//If the table is full, no free sector can be returned
	if (*sector_id == -1)
		return ER_ALLOCATION_TABLE_FULL;

	//Returns the id of the allocated sector
	return NO_ERROR;
}

ErrorCode SectorManager::DeallocateSector(SectorID sector_id) {
	
	//Check if sector number is in range
	if (sector_id < 0 || sector_id >= NUMBER_OF_SECTORS)
		return ErrorManager::error(__HERE__, ER_SECTOR_OUT_OF_RANGE, sector_id,NUMBER_OF_SECTORS-1);

	//Check if sector is actually allocated
	if (!(*allocation_table_).IsBitSet(sector_id)) {
		return ErrorManager::error(__HERE__, ER_SECTOR_NOT_USED, sector_id);
	}
	else {
		(*allocation_table_).ClearBit(sector_id);
		return NO_ERROR;
	}

}

bool SectorManager::IsSectorAllocated(SectorID sector_id) {
	return (*allocation_table_).IsBitSet(sector_id);
}

BYTE* SectorManager::GetSectorPointer(SectorID sector_id) {
	if (sector_id >= 0 && sector_id < NUMBER_OF_SECTORS)
		return storage_pointer_ + sector_id*sector_size_;
}
