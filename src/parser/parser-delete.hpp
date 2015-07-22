#ifndef PARSER_DELETE_HPP_
#define PARSER_DELETE_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"

class ParserDelete :
	public virtual ParserNode {

public:
	~ParserDelete ();

	std::string ToString () override;

protected:
};

class ParserDeleteStatement :
	public virtual ParserDelete,
	public virtual ParserRoot {

public:
	ParserDeleteStatement (yy::location loc);

protected:
	ErrorCode Compile () override;
	ErrorCode Prepare () override;
	ErrorCode Execute () override;

	std::string Print () override;
};

#endif // PARSER_DELETE_HPP_