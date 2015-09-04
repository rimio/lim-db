#ifndef QUERY_EXECUTE_SELECT_HPP_
#define QUERY_EXECUTE_SELECT_HPP_

#include "query-execution\query-execute.hpp"
#include "schema\table.hpp"
#include "metadata\database-value.hpp"
#include "parser\parser-node.hpp"
#include "parser\parser-column.hpp"
#include "parser\parser-table.hpp"
#include "parser\parser-select.hpp"
#include <vector>

class QueryExecuteSelect : QueryExecute {
public:
	QueryExecuteSelect(ParserTable *t, ParserSelect *select_reference);
	ErrorCode Execute() override;
	void Print(std::vector<std::vector<DatabaseValue>> values);
private:
	ParserTable *table_;
	ParserSelect *select_reference_;
};

#endif 