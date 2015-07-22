#ifndef PARSER_DROP_TABLE_HPP_
#define PARSER_DROP_TABLE_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"
#include "parser\parser-table.hpp"

class ParserDropTableStatement :
	public virtual ParserNode,
	public virtual ParserRoot {

public:
	ParserDropTableStatement (ParserTable *table, yy::location loc)
		: table_ (table) {

			setLocation (loc);
		};
	~ParserDropTableStatement ();

protected:
	ErrorCode Compile () override;
	ErrorCode Prepare () override { return NO_ERROR; }
	ErrorCode Execute () override;

	std::string Print () override;
private:
	ParserTable *table_;
};
#endif // PARSER_DROP_TABLE_HPP_