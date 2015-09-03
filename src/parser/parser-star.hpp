#ifndef PARSER_STAR_CPP_
#define PARSER_STAR_CPP_

#include "parser\parser-node.hpp"
#include "parser\parser-table.hpp"

class ParserStar : public ParserNode {
public:
	ParserStar () { table_ = nullptr; };
	ParserStar (ParserTable* table) { table_ = table; };
protected:
	void GetChildren(std::vector<ParserNode *>* children) override {};
	ErrorCode TypeCheckPre(TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; };
	ErrorCode TypeCheckPost(TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; };

	ErrorCode NameResolvePre(NameResolveArg* arg, bool* stop_walk) override;
	ErrorCode NameResolvePost(NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; };

	ErrorCode ConstantFoldPost(void) override { return NO_ERROR; };
private:
	ParserTable *table_;
};

#endif