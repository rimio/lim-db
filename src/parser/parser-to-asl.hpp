#ifndef PARSER_TO_ASL_HPP_
#define PARSER_TO_ASL_HPP_

#include "base\error-codes.hpp"
#include "metadata\database-value.hpp"
#include "parser\parser-node.hpp"
#include "parser\parser-column.hpp"
#include "schema\attribute.hpp"
#include "parser\parser-table.hpp"

class ParserToASL {
public:
	static std::vector<std::vector<DatabaseValue>> ParserValueToDatabase (std::vector<std::vector<ParserNode *> *> *values);
	static std::vector<Attribute> ParserColumnToAttributes (ParserTable *table, std::vector<ParserColumn *>* columns);
};

#endif