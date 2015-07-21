#ifndef PT_ALTER_TABLE_HPP_
#define PT_ALTER_TABLE_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"

class PTAlterTableRoot :
	public virtual ParserNode,
	public virtual ParserRoot {

public:
	PTAlterTableRoot (yy::location loc) { setLocation (loc); };
	~PTAlterTableRoot ();

protected:
	PTAlterTableRoot () {};

	ErrorCode Compile () override;
	ErrorCode Prepare () override { return NO_ERROR; };
	ErrorCode Execute () override;

	std::string Print() override;
};

#endif // PT_ALTER_TABLE_HPP_