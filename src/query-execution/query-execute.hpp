#ifndef QUERY_EXECUTE_HPP_
#define QUERY_EXECUTE_HPP_

#include "base\error-codes.hpp"

class QueryExecute {
public:
	virtual ErrorCode Execute() = 0;
};

#endif