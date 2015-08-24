#ifndef QUERY_EXECUTE_INSERT_HPP_
#define QUERY_EXECUTE_INSERT_HPP_

#include "query-execution\query-execute.hpp"
#include "schema\table.hpp"
#include "metadata\database-value.hpp"
#include <vector>

class QueryExecuteInsert : QueryExecute {
public:
	QueryExecuteInsert(std::vector<std::vector<DatabaseValue>> list, Table* t) { (void)set_database_value_list(list); table_ = t; };
	ErrorCode Execute() override;
	void set_database_value_list(std::vector<std::vector<DatabaseValue>> list);
	std::vector<std::vector<DatabaseValue>> database_value_list() { return database_value_list_; }

private:
	std::vector<std::vector<DatabaseValue>> database_value_list_;
	Table* table_;
};

#endif 