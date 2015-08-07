#ifndef PARSER_UPDATE_HPP_
#define PARSER_UPDATE_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"

class ParserUpdate :
	public virtual ParserNode {

public:
	virtual ~ParserUpdate ();

	std::string ToString () override;

protected:

	// Override virtual functions from ParserNode
	ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode ConstantFoldPost (void) override { return NO_ERROR; }

	void GetChildren (std::vector<ParserNode *>* children) {};
};

class ParserUpdateStatement :
	public virtual ParserUpdate,
	public virtual ParserRoot {

public:
	ParserUpdateStatement (yy::location loc);

	ErrorCode Compute(DataType expected_type_, ParserNode* *value) override { return NO_ERROR; };

protected:
	ErrorCode Compile () override;
	ErrorCode Prepare () override;
	ErrorCode Execute () override;

	std::string Print () override;
};

#endif // PARSER_UPDATE_HPP_