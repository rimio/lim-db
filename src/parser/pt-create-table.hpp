#ifndef PT_CREATE_TABLE_HPP_
#define PT_CREATE_TABLE_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"
#include "parser\pt-table.hpp"
#include "parser\pt-column.hpp"

class PTCreateTableRoot :
	public virtual ParserNode,
	public virtual ParserRoot {

public:
	PTCreateTableRoot (PTTableNode* table,
					   std::vector<PTColumnNode*>* columns,
					   yy::location loc)
		: table_(table),
		  columns_(columns) {

			setLocation (loc);
		};
	~PTCreateTableRoot ();

protected:
	PTCreateTableRoot () {};

	ErrorCode Compile () override;
	ErrorCode Prepare () override { return NO_ERROR; };
	ErrorCode Execute () override;

	std::string Print() override;
private:
	PTTableNode* table_;
	std::vector<PTColumnNode *>* columns_;
};

#endif // PT_CREATE_TABLE_HPP_