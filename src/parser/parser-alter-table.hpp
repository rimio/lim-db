#ifndef PARSER_ALTER_TABLE_HPP_
#define PARSER_ALTER_TABLE_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"

class ParserAlterTableStatement :
	public virtual ParserNode,
	public virtual ParserRoot {

public:
	ParserAlterTableStatement (yy::location loc) { setLocation (loc); };
	~ParserAlterTableStatement ();

	ErrorCode Compute (DataType expected_type, ParserNode* *value) override { return NO_ERROR; };

protected:
	ParserAlterTableStatement () {};

	ErrorCode Compile () override;
	ErrorCode Prepare () override { return NO_ERROR; };
	ErrorCode Execute () override;

	std::string Print() override;

	// Override virtual functions from ParserNode
	ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode ConstantFoldPost (void) override { return NO_ERROR; }

	void GetChildren (std::vector<ParserNode *>* children) {}
};

#endif // PARSER_ALTER_TABLE_HPP_