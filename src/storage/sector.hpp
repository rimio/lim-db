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
	SECTOR_HEAP,
	SECTOR_INDEX
};

class Sector {
public:
	BYTE* get_data();

	void UseSector(Sector *sector_p, int meta_data_size);

protected:
	Sector(){};

private:
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

	// Sector actual data starts here. It should have 6k - offset of Sector::data in Sector.
	BYTE *data_;
};
#endif // SECTOR_HPP_