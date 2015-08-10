#ifndef PARSER_DELETE_HPP_
#define PARSER_DELETE_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"

class ParserDelete :
	public virtual ParserNode {

public:
	virtual ~ParserDelete ();

	std::string ToString () override;

protected:
	// Override virtual functions from ParserNode
	ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode ConstantFoldPost (void) override { return NO_ERROR; }

	void GetChildren (std::vector<ParserNode *>* children) {}
};

class ParserDeleteStatement :
	public virtual ParserDelete,
	public virtual ParserRoot {

public:
	ParserDeleteStatement (yy::location loc);

	ErrorCode Compute(DataType expected_type, ParserNode* *value) override { return NO_ERROR; };

protected:
	ErrorCode Compile () override;
	ErrorCode Prepare () override;
	ErrorCode Execute () override;

	std::string Print () override;
};

#endif // PARSER_DELETE_HPP_