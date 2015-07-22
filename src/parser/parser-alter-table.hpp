#ifndef PARSER_ALTER_TABLE_HPP_
#define PARSER_ALTER_TABLE_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"

class ParserAlterTableStatement :
	public virtual ParserNode,
	public virtual ParserRoot {

public:
	ParserAlterTableStatement (yy::location loc) { setLocation (loc); };
	~ParserAlterTableStatement ();

protected:
	ParserAlterTableStatement () {};

	ErrorCode Compile () override;
	ErrorCode Prepare () override { return NO_ERROR; };
	ErrorCode Execute () override;

	std::string Print() override;
};

#endif // PARSER_ALTER_TABLE_HPP_