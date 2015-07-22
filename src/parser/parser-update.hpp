#ifndef PARSER_UPDATE_HPP_
#define PARSER_UPDATE_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"

class ParserUpdate :
	public virtual ParserNode {

public:
	~ParserUpdate ();

	std::string ToString () override;

protected:
};

class ParserUpdateStatement :
	public virtual ParserUpdate,
	public virtual ParserRoot {

public:
	ParserUpdateStatement (yy::location loc);

protected:
	ErrorCode Compile () override;
	ErrorCode Prepare () override;
	ErrorCode Execute () override;

	std::string Print () override;
};

#endif // PARSER_UPDATE_HPP_