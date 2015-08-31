#ifndef QUERY_EXECUTE_INSERT_HPP_
#define QUERY_EXECUTE_INSERT_HPP_

#include "query-execution\query-execute.hpp"
#include "schema\table.hpp"
#include "metadata\database-value.hpp"
#include "parser\parser-node.hpp"
#include "parser\parser-column.hpp"
#include <vector>

class QueryExecuteInsert : QueryExecute {
public:
	QueryExecuteInsert (Table* t) { table_ = t; };
	QueryExecuteInsert(Table* t, std::vector<Attribute> columns,
		std::vector<std::vector<DatabaseValue>> values);

	ErrorCode Execute() override;
private:
	std::vector<Attribute> columns_;
	std::vector<std::vector<DatabaseValue>> values_;
	Table* table_;
};

#endif 