#include "base\generic-operations.hpp"
#include "schema\schema-manager.hpp"
#include "statement-node.hpp"

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

ErrorCode CreateTableStatementNode::compile() {
	std::string table_name = table_->name();

	//Verify that the table name isn't already used
	if (SchemaManager::FindTable(table_name) != NULL)
		return ER_TABLE_ALREADY_EXISTS;

	for (ColumnIdentifierNode *attr = definition_; attr != NULL; attr = dynamic_cast<ColumnIdentifierNode *> (attr->getNext())) {
		std::string attr_name = attr->name();
		STRING_TO_LOWER(attr_name);
	}

	//Verify that all atrtribute names are different
	for (ColumnIdentifierNode * attr = definition_; attr != NULL; attr = dynamic_cast<ColumnIdentifierNode *> (attr->getNext())) {
		std::string s_attr = (attr->name());
		for (ColumnIdentifierNode *attr2 = dynamic_cast<ColumnIdentifierNode *>(attr->getNext()); attr2 != NULL; attr2 = dynamic_cast<ColumnIdentifierNode *> (attr2->getNext())){
			std::string s_attr2 = attr2->name();
			if (s_attr.compare(s_attr2) == 0)
				return ER_SAME_ATTRIBUTE;
		}
	}
	return NO_ERROR;
}
 
 ErrorCode CreateTableStatementNode::execute() {
	printf("Se creeaza tabelul %s \n", table_->name());
	Table *t = new Table();

	t->set_table_name(table_->name()); 
	
	for (ColumnIdentifierNode * attr = definition_; attr != NULL; attr = dynamic_cast<ColumnIdentifierNode * > (attr->getNext())) {
		std::string s_attr = attr->name();
		s_attr.erase(0,1);
		t->AddAttribute(s_attr, (attr->getDataType()));
	}
	
	ErrorCode er = SchemaManager::AddTable(t);
	
	delete t;

	return NO_ERROR;
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