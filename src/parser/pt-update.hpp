#ifndef PT_UPDATE_HPP_
#define PT_UPDATE_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"

class PTUpdateNode :
	public virtual ParserNode {

public:
	~PTUpdateNode ();

	std::string ToString () override;

protected:
};

class PTUpdateRoot :
	public virtual PTUpdateNode,
	public virtual ParserRoot {

public:
	PTUpdateRoot (yy::location loc);

protected:
	ErrorCode Compile () override;
	ErrorCode Prepare () override;
	ErrorCode Execute () override;

	std::string Print () override;
};

#endif // PT_UPDATE_HPP_