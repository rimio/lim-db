#ifndef PT_SELECT_HPP_
#define PT_SELECT_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"
#include "parser\pt-table.hpp"
#include "parser\pt-column.hpp"

class PTSelectNode :
	public virtual ParserNode {

public:
	~PTSelectNode ();

	std::string ToString () override;

protected:
	
	PTTableNode* from_;
	std::vector<ParserNode *>* list_;
};

class PTSelectRoot :
	public virtual PTSelectNode,
	public virtual ParserRoot {

public:
	PTSelectRoot (std::vector<ParserNode *>* list, PTTableNode* from,
				  yy::location loc);

protected:
	ErrorCode Compile () override;
	ErrorCode Prepare () override;
	ErrorCode Execute () override;

	std::string Print () override;
};

#endif // PT_SELECT_HPP_