#ifndef SECTOR_HPP_
#define SECTOR_HPP_

#include "base\error-manager.hpp"
#include "base\error-codes.hpp"
#include "base\generic-type-definitions.hpp"
#include "base\generic-constants.hpp"


typedef INT64 SectorID;
typedef UINT16 SectorSize;

#define SECTOR_MAX_SIZE MAX_UINT16

enum SectorType
{
	SECTOR_UNKNOWN = 0,
	SECTOR_HEAD,
	SECTOR_DATA,
	SECTOR_INDEX
};

class Sector {
public:

protected:
	Sector(){};

	// TODO: Include here all data required
	SectorID self_ref_;

	// TODO: Will require a log ID.

	// Sector definition
	SectorType type_;

	// Memory related
	SectorSize free_;
	SectorSize max_contiguous_free_;

	// Size of data deleted and committed.
	SectorSize dead_;

	// Size of data deleted but not committed yet.
	SectorSize deleted_;

	// Statistics Related
};
#endif // SECTOR_HPP_