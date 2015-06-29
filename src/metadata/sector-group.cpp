#include "sector-group.hpp"


SectorGroup::SectorGroup ()
{
	// Add code if required
}

SectorGroup::~SectorGroup()
{
	// Nothing to free so far
}

// Add a new sector to the group
//
// Return error code.
ErrorCode SectorGroup::AppendSector (SectorID sector_id)
{
	sectors_.push_back (sector_id);
	return ErrorCode::NO_ERROR;
}