#ifndef SECTOR_MANAGER_HPP_
#define SECTOR_MANAGER_HPP_

#include "base\bitmap.hpp"
#include "base\generic-type-definitions.hpp"

class SectorManager {
	public:
		//Constructor
		SectorManager(int sector_size);

		//Finds and returns ID to a free sector
		int allocate_sector();

		//Deallocates a sector
		bool deallocate_sector(int sector_number);
	protected:
	private:
		//Instance of Bitmap for tracking usage of sectors
		Bitmap *allocation_table_;
		//Keeps record of the size of one sector
		int sector_size_;
		//Pointer to the last sector used
		int *last_used_;
		//Points to the start of the memory allocated
		int *storage_pointer_;
};
#endif