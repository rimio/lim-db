#include "parser\parser-column.hpp"
#include "boot\boot.hpp"
#include "parser\parser-table.hpp"

std::string ParserColumn::ToString () {
	return name_;
}

ErrorCode ParserColumn::NameResolvePost(NameResolveArg* arg, bool* stop_walk) {	

	// Check if column is bounded to a specific table
	if (table_name() != "") {
		auto pt = arg->tables_stack_.top();
		
		for (auto tbl = pt.begin(); tbl != pt.end(); tbl++) {
			if (table_name() == (*tbl)->name()) {
				this->resolved_to_ = *tbl;

				auto attributes = (*tbl)->table()->get_table_attributes();

				for (auto atr : attributes) {
					if (atr.get_name() == name_){
						this->data_type_ = atr.get_type();
						return NO_ERROR;
					}
				}
			}
		}
	}
	
	// Otherwise, check with all possible tables
	else {
		auto pt = arg->tables_stack_.top();
		
		if (pt.size() == 0) {
			return ErrorManager::error(__HERE__, ER_INEXISTENT_COLUMN, name_.c_str(), table_name_.c_str());
		}
		
		for (auto tbl = pt.begin(); tbl != pt.end(); tbl++) {
			auto attributes = (*tbl)->table()->get_table_attributes();

			for (auto atr : attributes) {
				if (atr.get_name() == name_) {
					this->data_type_ = atr.get_type();
					return NO_ERROR;
				}
			}
		}
	}

	return ErrorManager::error(__HERE__, ER_INEXISTENT_COLUMN, name_.c_str(),table_name_.c_str());
}

ErrorCode ParserColumn::TypeCheckPre(TypeCheckArg* arg, bool* stop_walk) {
	std::vector<DataType> column;

	switch (this->data_type()) {
	case DB_INTEGER :
		column.push_back(DB_ANY);
		break;
	case DB_FLOAT :
		column.push_back(DB_INTEGER);
		column.push_back(DB_FLOAT);
		column.push_back(DB_STRING);
		break;
	case DB_STRING : 
		column.push_back(DB_INTEGER);
		//column.push_back(DB_FLOAT);
		column.push_back(DB_STRING);
		break;
	case DB_BOOLEAN:
		column.push_back(DB_ANY);
		break;
	default :
		break;
	}

	(*arg).tables_and_columns_stack_.top().back().push_back(column);
	
	return NO_ERROR;
}