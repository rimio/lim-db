#include "query-execution\scan-value-list.hpp"

ScanValueList::ScanValueList(std::vector<std::vector<DatabaseValue>> list) {
	list_.assign(list.begin(), list.end());
	next_ = 0;
}

std::vector<DatabaseValue> ScanValueList::Next() {
	return list_.at(next_++);
}