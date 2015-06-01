#include "storage/sector.hpp"

#include <stddef.h>
#include <assert.h>

Sector::Sector ()
{
	self_ref_ = 0;
	type_ = SECTOR_UNKNOWN;

	free_ = 0;
}

void Sector::UseSector (Sector *sector_p, SectorID id, SectorType type)
{
	// Should we automatically get ID using sector pointer
	sector_p->self_ref_ = id;
	
	sector_p->type_ = type;

	sector_p->free_ = SECTOR_MAX_SIZE - offsetof (Sector, data_);
}

ErrorCode Sector::ScanStart (void ** ptr)
{
	assert (ptr != NULL);

	SectorSize first_entry_size = *(SectorSize *) data_;

	if (first_entry_size == 0)
	{
		*ptr = NULL;
	}
	else
	{
		*ptr = (void *) data_;
	}
	return ErrorCode::NO_ERROR;
}

ErrorCode Sector::ScanIterate (void ** ptr)
{
	assert (ptr != NULL && *ptr != NULL);

	SectorSize entry_size = *(SectorSize *) (*ptr);
	assert (entry_size != 0);

	*ptr = ((char *) (*ptr)) + entry_size;
	entry_size = *(SectorSize *) (*ptr);
	if (entry_size == 0)
	{
		*ptr = NULL;
	}
	else
	{
		/* Valid pointer. */
	}
	return ErrorCode::NO_ERROR;
}