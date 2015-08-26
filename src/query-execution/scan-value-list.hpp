#ifndef SCAN_VALUE_LIST_HPP
#define SCAN_VALUE_LIST_HPP

#include "query-execution\scan.hpp"
#include "metadata\database-value.hpp"
#include <vector>

class ScanValueList: Scan {
public:
	ScanValueList(std::vector<std::vector<DatabaseValue>> list);
	void Start() override { next_ = 0; }
	void End() override {};
	bool HasNext() { return (next_ < list_.size()); }
	std::vector<DatabaseValue> Next();

private:
	std::vector<std::vector<DatabaseValue>> list_;
	int next_;
};

#endif