#include "parser-value.hpp"
#include "base\error-manager.hpp"

/*

ErrorCode ParserValue::TypeCheckPre(TypeCheckArg* arg, bool* stop_walk) {
	std::vector< DataType> column = (*arg).tables_and_columns_stack_.top().back().back();
	(*arg).tables_and_columns_stack_.top().back().pop_back();

	if (column.at(0) = DB_ANY) return NO_ERROR;

	for (auto col : column)
		if (col == value_->get_type())
			return NO_ERROR;

	return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);
}

*/