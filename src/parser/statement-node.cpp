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

std::string CreateIndexStatementNode::print ()
{
	return
		std::string ("CREATE INDEX ");
}

std::string DropIndexStatementNode::print ()
{
	return
		std::string ("DROP INDEX ");
}