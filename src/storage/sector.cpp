#include "storage/sector.hpp"

BYTE* Sector::get_data() {
	return data_;
}

void Sector::UseSector(Sector *sector_p, int meta_data_size)
{
	data_ = (BYTE*)sector_p + meta_data_size;
	sector_p->free_ = SECTOR_MAX_SIZE - offsetof(Sector, data_);
}
