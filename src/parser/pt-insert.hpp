#ifndef PT_INSERT_HPP_
#define PT_INSERT_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"
#include "parser\pt-table.hpp"
#include "parser\pt-column.hpp"

class PTInsertNode :
	public virtual ParserNode {

public:
	~PTInsertNode ();

	std::string ToString () override;

protected:
	PTInsertNode () : table_ (NULL), columns_ (NULL), values_ (NULL) {};
	
	PTTableNode* table_;
	std::vector<PTColumnNode *>* columns_;

	std::vector<std::vector<ParserNode *> *> *values_;
};

class PTInsertRoot :
	public virtual PTInsertNode,
	public virtual ParserRoot {

public:
	PTInsertRoot (PTTableNode* table, std::vector<PTColumnNode *>* columns,
				  std::vector<std::vector<ParserNode *> *> *values,
				  yy::location loc);

protected:
	ErrorCode Compile () override;
	ErrorCode Prepare () override;
	ErrorCode Execute () override;

	std::string Print () override;
};

#endif // PT_INSERT_HPP_