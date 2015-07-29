#include "parser\parser-column.hpp"
#include "boot\boot.hpp"
#include "parser\parser-table.hpp"

std::string ParserColumn::ToString () {
	return name_;
}

ErrorCode ParserColumn::NameResolvePost(NameResolveArg* arg, bool* stop_walk) {
	Table *table;
	std::vector<Attribute> attributes;
	// Check if column is bounded to a specific table
	if (table_name() != "") {
		table = GET_SCHEMA_MANAGER()->FindTable(table_name());
		attributes = table->get_table_attributes();
		
		for (auto atr : attributes) {
			if (atr.get_name() == name_)
				return NO_ERROR;
		}
	}
	// Otherwise, check with all possible tables
	else {
		std::vector <ParserTable*> pt = arg->tables_stack_.top();
		
		if (pt.size() == 0) {
			*stop_walk = true;
			return ErrorManager::error(__HERE__, ER_INEXISTENT_COLUMN, name_, table_name_);
		}
		
		for (auto tbl = pt.begin(); tbl != pt.end(); tbl++) {
			attributes = (*tbl)->table()->get_table_attributes();

			for (auto atr : attributes) {
				if (atr.get_name() == name_)
					return NO_ERROR;
			}
		}
	}

	*stop_walk = true;
	return ErrorManager::error(__HERE__, ER_INEXISTENT_COLUMN, name_.c_str(),table_name_.c_str());
}