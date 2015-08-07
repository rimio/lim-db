#ifndef PT_CREATE_TABLE_HPP_
#define PT_CREATE_TABLE_HPP_

#include "parser\parser-node.hpp"
#include "parser\parser-root.hpp"
#include "parser\parser-table.hpp"
#include "parser\parser-column.hpp"

class ParserCreateTableStatement :
	public virtual ParserNode,
	public virtual ParserRoot {

public:
	ParserCreateTableStatement (ParserTable* table,
					   std::vector<ParserColumn *>* columns,
					   yy::location loc)
		: table_(table),
		  columns_(columns) {

			setLocation (loc);
		};
	~ParserCreateTableStatement ();

	ErrorCode Compute(DataType expected_type_, ParserNode* *value) override { return NO_ERROR; };

protected:
	ParserCreateTableStatement () {};

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

	void GetChildren (std::vector<ParserNode *>* children);

private:
	ParserTable* table_;
	std::vector<ParserColumn *>* columns_;
};

#endif // PT_CREATE_TABLE_HPP_