#ifndef PT_DELETE_HPP_
#define PT_DELETE_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"

class PTDeleteNode :
	public virtual ParserNode {

public:
	~PTDeleteNode ();

	std::string ToString () override;

protected:
};

class PTDeleteRoot :
	public virtual PTDeleteNode,
	public virtual ParserRoot {

public:
	PTDeleteRoot (yy::location loc);

protected:
	ErrorCode Compile () override;
	ErrorCode Prepare () override;
	ErrorCode Execute () override;

	std::string Print () override;
};

#endif // PT_DELETE_HPP_