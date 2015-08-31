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
	QueryExecuteInsert(Table* t, std::vector<ParserColumn *>* columns,
		std::vector<std::vector<ParserNode *> *> * values) { table_ = t; columns_ = columns; values_ = values; };

	ErrorCode Execute() override;
private:
	std::vector<ParserColumn *>* columns_;
	std::vector<std::vector<ParserNode *> *> * values_;
	Table* table_;
};

#endif 