#include "query-execution\scan-serialized-list.hpp"

void ScanSerializedList::Start() {
	last_sector_used_ = -1;
	last_row_used_ = -1;
}

ErrorCode ScanSerializedList::Next(RowData* row, bool* has_next) {
	ErrorCode er = NO_ERROR;
	BYTE *start;
	er = table_->table_data()->RetrieveFromSector(&last_sector_used_, &last_row_used_, &start, has_next);

	if (er != NO_ERROR || !(*has_next)) {
		return er;
	}

	start = row->DeserializeRow(start);
	
	return NO_ERROR;
}