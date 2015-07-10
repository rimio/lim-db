#include "base\generic-operations.hpp"
#include "schema\schema-manager.hpp"
#include "statement-node.hpp"
#include "base\generic-operations.hpp"

#include <map>

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

 bool CreateTableStatementNode::compile() {
	std::string table_name = table_->toString();
	ColumnIdentifierNode *attribute = new ColumnIdentifierNode("");
	ColumnIdentifierNode *next_attribute = new ColumnIdentifierNode("");
	//Verify that the table name isn't already used
	if (!(SchemaManager::find_table(table_name))) {
		//Verify that all atrtribute names are different
		for (attribute = definition_; attribute != NULL; attribute = dynamic_cast<ColumnIdentifierNode *> (attribute->getNext())) {
			std::string s_attribute = (attribute->toString());
			string_to_lower(s_attribute);
			for (next_attribute = dynamic_cast<ColumnIdentifierNode *>(attribute->getNext()); next_attribute != NULL; next_attribute = dynamic_cast<ColumnIdentifierNode *> (next_attribute->getNext())){
				std::string s_next_attribute = next_attribute->toString();
				string_to_lower(s_next_attribute);
				if (s_attribute.compare(s_next_attribute) == 0)
					return false;
			}
		}
		return true;
	}
	else {
		return false;
	} 
} 
 
 bool CreateTableStatementNode::execute() {
	Table *t = new Table();
	ColumnIdentifierNode *attribute = new ColumnIdentifierNode(NULL, NULL);
	t->set_table_name(table_->toString()); 
	for (attribute = definition_; attribute->getNext() != NULL; attribute = dynamic_cast<ColumnIdentifierNode * > (attribute->getNext())) {
		std::string str_attribute = attribute->toString();
		str_attribute.erase(0, (table_->toString().length() + 1));
		Attribute *a = new Attribute((attribute->getDataType()), str_attribute);
		t->add_attribute(*a);
	}
	SchemaManager::add_table(t);
	return true;
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