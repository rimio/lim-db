#ifndef PARSER_SELECT_HPP_
#define PARSER_SELECT_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"
#include "parser\parser-table.hpp"
#include "parser\parser-column.hpp"

class ParserSelect :
	public virtual ParserNode {

public:
	~ParserSelect ();

	std::string ToString () override;

protected:
	
	ParserTable* from_;
	std::vector<ParserNode *>* list_;
};

class ParserSelectStatement :
	public virtual ParserSelect,
	public virtual ParserRoot {

public:
	ParserSelectStatement (std::vector<ParserNode *>* list, ParserTable* from,
						   yy::location loc);

protected:
	ErrorCode Compile () override;
	ErrorCode Prepare () override;
	ErrorCode Execute () override;

	std::string Print () override;
};

#endif // PARSER_SELECT_HPP_