#include "query-execute-select.hpp"
#include "query-execution\scan-serialized-list.hpp"

QueryExecuteSelect::QueryExecuteSelect(Table *t, std::vector<Attribute> columns) {
	table_ = t;
	columns_.clear();
	columns_.assign(columns.begin(), columns.end());
}

ErrorCode QueryExecuteSelect::Execute() {
	ErrorCode er = NO_ERROR;
	std::vector<std::vector<DatabaseValue>> values;
	std::vector<DatabaseValue> row_values;
	std::vector<DatabaseValue> insert_row;

	ScanSerializedList scan = ScanSerializedList(table_);
	scan.Start();
	RowData row = RowData(table_);
	bool has_next = true;

	while (scan.Next(&row, &has_next) == NO_ERROR && has_next) {
		insert_row.clear();
		row_values = row.values();
		for (auto col : columns_) {
			insert_row.push_back(row_values.at(col.position() - 1));
		}
		values.push_back(insert_row);
	}

	(void)Print(values);

	return er;
}

void QueryExecuteSelect::Print(std::vector<std::vector<DatabaseValue>> values) {
	// Print the headers
	for (auto col : columns_) {
		printf("%s ", col.name().c_str());
	}
	printf("\n");

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