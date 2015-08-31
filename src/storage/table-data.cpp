#include "storage\table-data.hpp"
#include "storage\data-sector.hpp"
#include "boot\boot.hpp"

ErrorCode TableData::InsertIntoSector(BYTE *start, int length) {
	ErrorCode er = NO_ERROR;
	bool row_inserted = false;
	DataSector *ds;
	for (auto sector : allocated_sectors_->sectors()) {
		ds = (DataSector*)GET_SECTOR_MANAGER()->GetSectorPointer(sector);
		er = ds->Insert(start, length,&row_inserted);
		if (row_inserted) {
			break;
		}
	}

	if (!row_inserted) {
		SectorID new_sector = 0;
		er = GET_SECTOR_MANAGER()->AllocateSector(&new_sector);

		if (er != NO_ERROR)
			return er;

		allocated_sectors_->AppendSector(new_sector);
		ds = reinterpret_cast<DataSector*> (GET_SECTOR_MANAGER()->GetSectorPointer(new_sector));

		er = ds->Insert(start, length,&row_inserted);

		if (er != NO_ERROR)
			return er;
	}

	return er;
}