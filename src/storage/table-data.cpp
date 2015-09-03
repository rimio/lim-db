#include "storage\table-data.hpp"
#include "storage\data-sector.hpp"
#include "boot\boot.hpp"
#include "storage\row-data.hpp"

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
		ds = (DataSector*) (GET_SECTOR_MANAGER()->GetSectorPointer(new_sector));
		ds->UseDataSector(ds);
		er = ds->Insert(start, length,&row_inserted);

		if (er != NO_ERROR)
			return er;
	}

	return er;
}

ErrorCode TableData::RetrieveFromSector(SectorID* last_sector_used, BYTE* last_row_used, BYTE **start, bool *has_next) {
	*has_next = true;
	
	if (*last_sector_used == -1)
		(*last_sector_used)++;

	if (*last_sector_used >= allocated_sectors_->sectors().size()) {
		*has_next = false;
		return NO_ERROR;
	}

	(*last_row_used)++;

	DataSector *ds;
	ds = (DataSector*) (GET_SECTOR_MANAGER()->GetSectorPointer(allocated_sectors_->sectors().at(*last_sector_used)));
	while (ds->num_rows() <= (*last_row_used)) {
		(*last_sector_used)++;
		if (*last_sector_used >= allocated_sectors_->sectors().size()) {
			*has_next = false;
			return NO_ERROR;
		}
		ds = (DataSector*) (GET_SECTOR_MANAGER()->GetSectorPointer(allocated_sectors_->sectors().at(*last_sector_used)));
		(*last_row_used) = 0;
	}

	(*start) = ds->Select(*last_row_used);
	return NO_ERROR;
}