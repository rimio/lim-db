#ifndef PT_DROP_TABLE_HPP_
#define PT_DROP_TABLE_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"
#include "parser\pt-table.hpp"

class PTDropTableRoot :
	public virtual ParserNode,
	public virtual ParserRoot {

public:
	PTDropTableRoot (PTTableNode *table, yy::location loc)
		: table_ (table) {

			setLocation (loc);
		};
	~PTDropTableRoot ();

protected:
	ErrorCode Compile () override;
	ErrorCode Prepare () override { return NO_ERROR; }
	ErrorCode Execute () override;

	std::string Print () override;
private:
	PTTableNode *table_;
};
#endif // PT_DROP_TABLE_HPP_