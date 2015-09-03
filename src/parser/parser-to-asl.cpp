#include "parser-to-asl.hpp"

std::vector<ParserColumn *> ParserToASL::ParserNodeToParserColumn(std::vector<ParserNode *>* list) {
	std::vector<ParserColumn *> result;

	for (auto node : *list) {
		result.push_back(dynamic_cast<ParserColumn*>(node));
	}

	return result;
}

std::vector<std::vector<DatabaseValue>> ParserToASL::ParserValueToDatabase
(std::vector<std::vector<ParserNode *> *> *values) {
	std::vector<std::vector<DatabaseValue>> list;
	std::vector<DatabaseValue> row;

	for (auto val_row : *values) {
		row.clear();
		for (auto val : *val_row) {
			row.push_back(val->computed_value());
		}
		list.push_back(row);
	}

	return list;
}

std::vector<Attribute> ParserToASL::ParserColumnToAttributes(ParserTable *table, std::vector<ParserColumn *>* columns) {
	std::vector<Attribute> result;
	auto attributes = table->table()->table_attributes();

	std::string col_name;
	for (auto col : *columns) {
		col_name = col->name();
		for (auto atr : attributes)
			if (col_name == atr.name()) {
				result.push_back(atr);
				break;
			}
	}

	return result;
}