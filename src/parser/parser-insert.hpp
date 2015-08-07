#ifndef PARSER_INSERT_HPP_
#define PARSER_INSERT_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"
#include "parser\parser-table.hpp"
#include "parser\parser-column.hpp"

class ParserInsert :
	public virtual ParserNode {

public:
	virtual ~ParserInsert ();

	std::string ToString () override;

protected:
	ParserInsert () : table_ (NULL), columns_ (NULL), values_ (NULL) {};

	// Override virtual functions from ParserNode
	ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }
	ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) override;
	ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) override { return NO_ERROR; }

	ErrorCode ConstantFoldPost (void) override { return NO_ERROR; }

	ErrorCode CheckValues();

	void GetChildren (std::vector<ParserNode *>* children);

	ErrorCode Compute(DataType expected_type_, ParserNode* *value) override { return NO_ERROR; };
	
	// Variable members
	ParserTable* table_;
	std::vector<ParserColumn *>* columns_;

	std::vector<std::vector<ParserNode *> *> *values_;
};

class ParserInsertStatement :
	public virtual ParserInsert,
	public virtual ParserRoot {

public:
	ParserInsertStatement (ParserTable* table, std::vector<ParserColumn *>* columns,
						   std::vector<std::vector<ParserNode *> *> *values,
						   yy::location loc);

protected:
	ErrorCode Compile () override;
	ErrorCode Prepare () override;
	ErrorCode Execute () override;

	std::string Print () override;
};

#endif // PARSER_INSERT_HPP_