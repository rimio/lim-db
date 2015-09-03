#ifndef QUERY_EXECUTE_SELECT_HPP_
#define QUERY_EXECUTE_SELECT_HPP_

#include "query-execution\query-execute.hpp"
#include "schema\table.hpp"
#include "metadata\database-value.hpp"
#include "parser\parser-node.hpp"
#include "parser\parser-column.hpp"
#include <vector>

class QueryExecuteSelect : QueryExecute {
public:
	QueryExecuteSelect(Table *t, std::vector<Attribute> columns);
	ErrorCode Execute() override;
	void Print(std::vector<std::vector<DatabaseValue>> values);
private:
	Table *table_;
	std::vector<Attribute> columns_;
};

#endif 