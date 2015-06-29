#ifndef SECTOR_GROUP_HPP_
#define SECTOR_GROUP_HPP_

#include "storage\sector.hpp"
#include <vector>

class SectorGroup
{
public:
	// Constructors
	SectorGroup ();

	/* Destructor */
	~SectorGroup ();

	ErrorCode AppendSector (SectorID sector_id);

private:
	std::vector<SectorID> sectors_;
};
#endif // SECTOR_GROUP_HPP_