#include "query-execution\scan-value-list.hpp"

ScanValueList::ScanValueList(std::vector<std::vector<DatabaseValue>> list) {
	list_.clear();
	list_.assign(list.begin(), list.end());
	next_ = 0;
}

ErrorCode ScanValueList::Next(std::vector<DatabaseValue> *row) {
	row->assign(list_.at(next_).begin(), list_.at(next_).end());
	next_++;
	return NO_ERROR;
}