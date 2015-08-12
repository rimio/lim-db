#ifndef PARSER_SELECT_HPP_
#define PARSER_SELECT_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"
#include "parser\parser-table.hpp"
#include "parser\parser-column.hpp"

class ParserSelect :
	public virtual ParserNode {

public:
	virtual ~ParserSelect ();

	std::string ToString () override;

protected:
	
	ParserTable* from_;
	std::vector<ParserNode *>* list_;

	// Override virtual functions from ParserNode
	ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode ConstantFoldPost (void) override { return NO_ERROR; }

	void GetChildren (std::vector<ParserNode *>* children);
};

class ParserSelectStatement :
	public virtual ParserSelect,
	public virtual ParserRoot {

public:
	ParserSelectStatement (std::vector<ParserNode *>* list, ParserTable* from,
						   yy::location loc);

protected:
	ErrorCode Compile () override;
	ErrorCode Prepare () override;
	ErrorCode Execute () override;

	std::string Print () override;
};

#endif // PARSER_SELECT_HPP_