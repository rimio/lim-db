#include "statement-node.hpp"

std::string SelectStatementNode::print ()
{
	return
		std::string ("SELECT ")
		+ (list_ != nullptr ? list_->printList (", ") : "")
		+ std::string (" FROM ")
		+ (from_ != nullptr ? from_->printList (", ") : "");
}

std::string InsertStatementNode::print ()
{
	return
		std::string ("INSERT INTO ")
		+ (table_ != nullptr ? table_->print () : "")
		+ std::string (" VALUES (")
		+ (values_ != nullptr ? values_->printList (", ") : "")
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

std::string CreateTableStatementNode::print ()
{
	return
		std::string ("CREATE TABLE ")
		+ (table_ != nullptr ? table_->print () : "")
		+ std::string ("(")
		+ (definition_ != nullptr ? definition_->printList (", ") : "")
		+ std::string (")");
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
		+ (table_ != nullptr ? table_->print () : "");
}

std::string DropIndexStatementNode::print ()
{
	return
		std::string ("DROP INDEX ");
}