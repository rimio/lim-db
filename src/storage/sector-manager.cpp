#include "storage\sector-manager.hpp"

#include <cstdlib>

#define NUMBER_OF_SECTORS 10

SectorManager::SectorManager(int sector_size) {
	allocation_table_ = new Bitmap(NUMBER_OF_SECTORS);
	storage_pointer_ = (int*)malloc(NUMBER_OF_SECTORS * sector_size);
	sector_size_ = sector_size;
	last_used_ = storage_pointer_;
}

int SectorManager::allocate_sector(){
	//If the table is full, no free sector can be returned
	if ((*allocation_table_).bitset_count() == NUMBER_OF_SECTORS) 
		return -1;
	
	//Starts to search for the desired empty space from the previous successful one
	int sector_id = (last_used_ - storage_pointer_) / sector_size_;
	
	while ((*allocation_table_).is_bit_set(sector_id)) {
		++sector_id;
		if (sector_id >= NUMBER_OF_SECTORS) sector_id = 0;
	}
	
	last_used_ = storage_pointer_ + sector_id*sector_size_;
	(*allocation_table_).set_bit(sector_id);

	//Returns a pointer to the allocated sector
	return sector_id;
}

bool SectorManager::deallocate_sector(int sector_id) {
	//Check if sector number is in range
	if (sector_id < 0 || sector_id >= NUMBER_OF_SECTORS) return false;

	//Check if sector is actually allocated
	if (!(*allocation_table_).is_bit_set(sector_id)) 
		return false;
	else {
		(*allocation_table_).clear_bit(sector_id);
		return true;
	}	
}
