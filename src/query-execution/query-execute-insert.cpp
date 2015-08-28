#include "query-execution\query-execute-insert.hpp"
#include "query-execution\scan-value-list.hpp"
#include "base\generic-operations.hpp"
#include "boot\boot.hpp"
#include "storage\row-data.hpp"

void QueryExecuteInsert::set_database_value_list(std::vector<ParserColumn *>* columns, 
	std::vector<std::vector<ParserNode *> *> * values) {
	auto attributes = table_->get_table_attributes();
	std::vector<std::vector<DatabaseValue>> list;
	std::vector<DatabaseValue> row;

	// If there are any blank columns, fill them with NULL values
	if (attributes.size() != values->at(0)->size()) {
		int size = table_->get_number_of_attributes();
		int* position = new int[size];
		for (int i = 0; i < size; i++)
			position[i] = size;

		// For each column search its position in the table's attibutes
		std::string col_name;
		for (int i = 0; i < columns->size(); i++) {
			col_name = columns->at(i)->name();
			for (int j = 0; j < attributes.size(); j++)
				if (col_name == attributes.at(j).get_name()) {
					position[attributes.at(j).get_position() - 1] = i;
					break;
				}
		}

		// Prepare the list of values for insertion
		DatabaseValue blank = DatabaseValue();
		for (auto val = values->begin(); val != values->end(); val++) {
			row.clear();
			for (int i = 0; i < attributes.size(); i++) {
				if (position[i] < size) {
					row.push_back((*val)->at(position[i])->computed_value());
				}
				else
					row.push_back(blank);
			}
			list.push_back(row);
		}

		delete position;
	}
	// Otherwise all the columns are used
	else {
		for (auto val = values->begin(); val != values->end(); val++) {
			row.clear();
			for (auto v = (*val)->begin(); v != (*val)->end(); v++) {
				row.push_back((*v)->computed_value());
			}
			list.push_back(row);
		}
	}

	database_value_list_.assign(list.begin(), list.end());
}

ErrorCode QueryExecuteInsert::InsertSector(BYTE *start, int length) {
	ErrorCode er = NO_ERROR;
	bool row_inserted = false;
	DataSector *ds;
	for (auto sector : table_->allocated_sectors()->sectors()) {
		ds = (DataSector*)GET_SECTOR_MANAGER()->GetSectorPointer(sector);
		er = ds->Insert(start, length);
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
		ds = reinterpret_cast<DataSector*> (GET_SECTOR_MANAGER()->GetSectorPointer(new_sector));

		er = ds->Insert(start, length);

		if (er != NO_ERROR)
			return er;
	}
}

ErrorCode QueryExecuteInsert::Execute() {
	ErrorCode er = NO_ERROR;
	ScanValueList *scan = new ScanValueList(database_value_list_);

	BYTE row_data_buffer[SECTOR_MAX_SIZE + INT32_ALIGNMENT];
	BYTE *start = PTR_ALIGN_UPPER(row_data_buffer, INT32_ALIGNMENT);
	BYTE *ptr;
	RowData* rd = new RowData(table_);
	std::vector<DatabaseValue> row;

	while (scan->HasNext()) {
		// Serialize row
		er = scan->Next(&row);

		if (er != NO_ERROR)
			return er;

		rd->set_data_values(row);
		ptr = rd->SerializeRow(table_, start);

		er = InsertSector(start, ptr - start);

		if (er != NO_ERROR)
			return er;
	}
	
	delete scan;
	delete rd;

	return er;
}