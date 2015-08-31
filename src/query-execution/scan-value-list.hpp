#ifndef SCAN_VALUE_LIST_HPP
#define SCAN_VALUE_LIST_HPP

#include "query-execution\scan.hpp"
#include "metadata\database-value.hpp"
#include "parser\parser-node.hpp"
#include <vector>

class ScanValueList: Scan {
public:
	ScanValueList(std::vector<std::vector<DatabaseValue>> list);
	void Start() override { next_ = 0; }
	void End() override {};
	bool HasNext() { return (next_ < list_.size()); }
	ErrorCode Next(std::vector<DatabaseValue> * row);

private:
	std::vector<std::vector<DatabaseValue>> list_;
	int next_;
};

#endif