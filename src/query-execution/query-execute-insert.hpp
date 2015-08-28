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
	
	void set_database_value_list(std::vector<ParserColumn *>* columns,
		std::vector<std::vector<ParserNode *> *> * values);

	std::vector<std::vector<DatabaseValue>> database_value_list() { return database_value_list_; }

	ErrorCode InsertSector(BYTE *start, int length);
	ErrorCode Execute() override;
private:
	std::vector<std::vector<DatabaseValue>> database_value_list_;
	Table* table_;
};

#endif 