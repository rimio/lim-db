#include "query-execution\query-execute-insert.hpp"
#include "query-execution\scan-value-list.hpp"
#include "base\generic-operations.hpp"
#include "boot\boot.hpp"
#include "storage\row-data.hpp"
#include "storage\table-data.hpp"

QueryExecuteInsert::QueryExecuteInsert(Table* t, std::vector<Attribute> columns,
	std::vector<std::vector<DatabaseValue>> values) {
	table_ = t;
	columns_.assign(columns.begin(), columns.end());
	values_.assign(values.begin(), values.end());
}

ErrorCode QueryExecuteInsert::Execute() {
	ErrorCode er = NO_ERROR;
	ScanValueList scan = ScanValueList(values_);

	BYTE row_data_buffer[SECTOR_MAX_SIZE + INT32_ALIGNMENT];
	BYTE *start = PTR_ALIGN_UPPER(row_data_buffer, INT32_ALIGNMENT);
	BYTE *ptr;
	RowData rd = RowData(table_);
	std::vector<DatabaseValue> row;
	TableData *td = table_->table_data();
	while (scan.HasNext()) {
		// Serialize row
		er = scan.Next(&row);

		if (er != NO_ERROR)
			return er;

		rd.set_data_values(row, columns_);
		ptr = rd.SerializeRow(start);

		er = td->InsertIntoSector(start, ptr - start);

		if (er != NO_ERROR)
			return er;
	}

	return er;
}