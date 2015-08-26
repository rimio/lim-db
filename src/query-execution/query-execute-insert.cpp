#include "query-execution\query-execute-insert.hpp"
#include "query-execution\scan-value-list.hpp"
#include "base\generic-operations.hpp"
#include "boot\boot.hpp"
#include "storage\row-data.hpp"

#define INT32_ALIGNMENT 4

void QueryExecuteInsert::set_database_value_list(std::vector<std::vector<DatabaseValue>> list) {
	database_value_list_.assign(list.begin(), list.end());
}

ErrorCode QueryExecuteInsert::Execute() {
	ErrorCode er = NO_ERROR;
	ScanValueList *scan = new ScanValueList(database_value_list_);

	while (scan->HasNext()) {
		// Serialize row
		
		auto row = scan->Next();
		auto rd = new RowData(table_);
	
		BYTE row_data_buffer[SECTOR_MAX_SIZE + INT32_ALIGNMENT];
		BYTE *start = PTR_ALIGN_UPPER(row_data_buffer, INT32_ALIGNMENT);

		rd->set_data_values(row);
		BYTE *ptr = rd->SerializeRow(table_, start);
		
		bool row_inserted = false;
		
		for (auto sector : table_->allocated_sectors()->sectors()) {
			DataSector *ds = (DataSector*)GET_SECTOR_MANAGER()->GetSectorPointer(sector);
			er = ds->Insert(start, ptr - start);
			if (er != ER_ALLOCATION_DATASECTOR_FULL) {
				row_inserted = true;
				break;
			}
		}
		
		if (!row_inserted) {
			SectorID new_sector = 0;
			er = GET_SECTOR_MANAGER()->AllocateSector(&new_sector);
			
			if (er != NO_ERROR)
				return er;

			table_->allocated_sectors()->AppendSector(new_sector);
			DataSector *ds = reinterpret_cast<DataSector*> (GET_SECTOR_MANAGER()->GetSectorPointer(new_sector));
			
			er = ds->Insert(start, ptr - start);
			
			if (er != NO_ERROR)
				return er;
		}
		
		delete rd;
	}
	
	return er;
}