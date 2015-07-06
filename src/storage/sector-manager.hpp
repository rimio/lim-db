#ifndef SECTOR_MANAGER_HPP_
#define SECTOR_MANAGER_HPP_

#include "base\bitmap.hpp"
#include "base\error-codes.hpp"
#include "base\error-manager.hpp"
#include "base\generic-type-definitions.hpp"
#include "storage\sector.hpp"

class SectorManager {
	public:
		//Constructor
		SectorManager();

		//Finds and returns ID to a free sector
		ErrorCode allocate_sector(int *sector_id);

		//Deallocates a sector
		ErrorCode deallocate_sector(const int sector_number, bool *finished);

		//Checks wether a sector is free ot not
		bool is_sector_allocated(const int sector_id);
	protected:
	private:
		//Instance of Bitmap for tracking usage of sectors
		Bitmap *allocation_table_;
		//Keeps record of the size of one sector
		int sector_size_;
		//Pointer to the last sector used
		int last_used_;
		//Points to the start of the memory allocated
		int *storage_pointer_;
};
#endif