#include "query-execution\scan-value-list.hpp"

ScanValueList::ScanValueList(std::vector<std::vector<ParserNode *> *> *list) {
	list_.clear();
	std::vector<DatabaseValue> row;
	for (auto r : (*list)) {
		row.clear();
		for (auto i : (*r)) {
			row.push_back(i->computed_value());
		}
		list_.push_back(row);
	}
	next_ = 0;
}

ErrorCode ScanValueList::Next(std::vector<DatabaseValue> *row) {
	row->assign(list_.at(next_).begin(), list_.at(next_).end());
	next_++;
	return NO_ERROR;
}