#ifndef PARSER_INSERT_HPP_
#define PARSER_INSERT_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"
#include "parser\parser-table.hpp"
#include "parser\parser-column.hpp"

class ParserInsert :
	public virtual ParserNode {

public:
	~ParserInsert ();

	std::string ToString () override;

protected:
	ParserInsert () : table_ (NULL), columns_ (NULL), values_ (NULL) {};
	
	ParserTable* table_;
	std::vector<ParserColumn *>* columns_;

	std::vector<std::vector<ParserNode *> *> *values_;
};

class ParserInsertStatement :
	public virtual ParserInsert,
	public virtual ParserRoot {

public:
	ParserInsertStatement (ParserTable* table, std::vector<ParserColumn *>* columns,
						   std::vector<std::vector<ParserNode *> *> *values,
						   yy::location loc);

protected:
	ErrorCode Compile () override;
	ErrorCode Prepare () override;
	ErrorCode Execute () override;

	std::string Print () override;
};

#endif // PARSER_INSERT_HPP_