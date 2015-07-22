#ifndef PARSER_DROP_TABLE_HPP_
#define PARSER_DROP_TABLE_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"
#include "parser\parser-table.hpp"

class ParserDropTableStatement :
	public virtual ParserNode,
	public virtual ParserRoot {

public:
	ParserDropTableStatement (ParserTable *table, yy::location loc)
		: table_ (table) {

			setLocation (loc);
		};
	~ParserDropTableStatement ();

protected:

	// Override virtual functions from ParserRoot
	ErrorCode Compile () override;
	ErrorCode Prepare () override { return NO_ERROR; }
	ErrorCode Execute () override;

	std::string Print () override;

	// Override virtual functions from ParserNode
	ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode ConstantFoldPost (void) override { return NO_ERROR; }

	void GetChildren (std::vector<ParserNode *>* children);

private:
	ParserTable *table_;
};
#endif // PARSER_DROP_TABLE_HPP_