#include "base\generic-operations.hpp"
#include "schema\schema-manager.hpp"
#include "statement-node.hpp"

#include <map>

StatementNode::~StatementNode() {}

std::string SelectStatementNode::print ()
{
	return
		std::string ("SELECT ")
		//+ (list_ != nullptr ? list_->printList (", ") : "")
		+ std::string (" FROM ")
		//+ (from_ != nullptr ? from_->printList (", ") : "")
		;
}

std::string InsertStatementNode::print ()
{
	return
		std::string ("INSERT INTO ")
		//+ (table_ != nullptr ? table_->print () : "")
		+ std::string (" VALUES (")
		//+ (values_ != nullptr ? values_->printList (", ") : "")
		+ std::string (")");
}

std::string DeleteStatementNode::print ()
{
	return
		std::string ("DELETE");
}

std::string UpdateStatementNode::print ()
{
	return
		std::string ("UPDATE");
}

DropTableStatementNode::~DropTableStatementNode(){
	delete table_;
}

std::string CreateIndexStatementNode::print ()
{
	return
		std::string ("CREATE INDEX ");
}

std::string DropTableStatementNode::print ()
{
	return
		std::string ("DROP TABLE ")
		//+ (table_ != nullptr ? table_->print () : "")
		;
}

ErrorCode DropTableStatementNode::compile() {
	//Verify that the table name exists
	if (GET_SCHEMA_MANAGER()->FindTable(table_->name()) == NULL)
		return ErrorManager::error(__HERE__, ER_TABLE_DOES_NOT_EXIST, table_->name().c_str());
	return NO_ERROR;
}

ErrorCode DropTableStatementNode::execute() {
	ErrorCode er = GET_SCHEMA_MANAGER()->DropTable(table_->name());
	return er;
}

std::string DropIndexStatementNode::print ()
{
	return
		std::string ("DROP INDEX ");
}