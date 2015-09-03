#include "parser/parser-star.hpp"
#include "parser/parser-column.hpp"

ErrorCode ParserStar::NameResolvePre(NameResolveArg* arg, bool* stop_walk) {
	std::vector<ParserColumn*> expansion;
	std::vector<Attribute> attributes;

	// If STAR is resolved to a table expand only its columns
	if (table_ != nullptr) {
		attributes = table_->table()->table_attributes();
		for (auto atr : attributes) {
			expansion.push_back(new ParserColumn(atr.name(), 
				atr.type(), table_->table()->table_name(), table_));
		}
	} 
	// Otherwise expand columns from all tables in the current node
	else {
		auto pt = arg->tables_stack_.top();

		for (auto tbl = pt.begin(); tbl != pt.end(); tbl++) {
			attributes = (*tbl)->table()->table_attributes();

			for (auto atr : attributes) {
				expansion.push_back(new ParserColumn(atr.name(),
					atr.type(), (*tbl)->table()->table_name(), *tbl));
			}
		}
	}
	// Insert the expanded columns
	for (int i = 0; i < (*arg->reference_to_list_).size(); i++) {
		if ((*arg->reference_to_list_).at(i) == this) {
			(*arg->reference_to_list_).erase((*arg->reference_to_list_).begin() + i );
			(*arg->reference_to_list_).insert((*arg->reference_to_list_).begin() + i, expansion.begin(), expansion.end());
			break;
		}
	}
	return NO_ERROR;
}