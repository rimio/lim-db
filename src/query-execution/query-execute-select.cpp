#include "query-execute-select.hpp"
#include "query-execution\scan-serialized-list.hpp"

QueryExecuteSelect::QueryExecuteSelect(ParserTable *t, ParserSelect* select_reference) {
	table_ = t;
	select_reference_ = select_reference;
}

ErrorCode QueryExecuteSelect::Execute() {
	ErrorCode er = NO_ERROR;
	std::vector<DatabaseValue> row_values;

	ScanSerializedList scan = ScanSerializedList(table_->table());
	scan.Start();
	RowData row = RowData(table_->table());
	bool has_next = true;

	while (scan.Next(&row, &has_next) == NO_ERROR && has_next) {
		row_values = row.values();
		table_->set_active_row(&row_values);
		er = select_reference_->ConstantFold();
		if (er != NO_ERROR)
			return er;
	}

	return er;
}

void QueryExecuteSelect::Print(std::vector<std::vector<DatabaseValue>> values) {
	// Print the values
	for (auto val : values) {
		for (int i = 0; i < val.size(); i++) {
			if (val.at(i).is_null()) {
				printf("IS NULL ");
			}
			else switch (val.at(i).data_type()) {
			case DB_INTEGER:
				printf("%d ", val.at(i).int_value());
				break;
			case DB_FLOAT:
				printf("%f ", val.at(i).float_value());
				break;
			case DB_STRING:
				printf("%s ", val.at(i).string_value().c_str());
				break;
			}
		}
		printf("\n");
	}

	printf("Nr rows printed: %d\n", values.size());
}