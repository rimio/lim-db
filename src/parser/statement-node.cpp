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
		return ErrorManager::error(__HERE__, ER_TABLE_ALREADY_EXISTS, table_->name().c_str());
	
	//Lowercase all the attributes
	std::string attr_name;
	for (ColumnIdentifierNode *attr = definition_; attr != NULL; attr = dynamic_cast<ColumnIdentifierNode *> (attr->getNext())) {
		attr_name = attr->name();
		STRING_TO_LOWER(attr_name);
		attr -> set_name( attr_name );
	}

	//Verify that all atrtribute names are different
	for (ColumnIdentifierNode * attr = definition_; attr != NULL; attr = dynamic_cast<ColumnIdentifierNode *> (attr->getNext())) {
		for (ColumnIdentifierNode *attr2 = dynamic_cast<ColumnIdentifierNode *>(attr->getNext()); attr2 != NULL; attr2 = dynamic_cast<ColumnIdentifierNode *> (attr2->getNext())){
			if (attr->name().compare(attr2->name()) == 0)
				return ErrorManager::error(__HERE__, ER_SAME_ATTRIBUTE, attr->name().c_str());
		}
	}
	return NO_ERROR;
}
 
 ErrorCode CreateTableStatementNode::execute() {
	printf("Se creeaza tabelul %s \n", table_->name().c_str());
	Table *t = new Table();

	t->set_table_name(table_->name()); 
	
	for (ColumnIdentifierNode * attr = definition_; attr != NULL; attr = dynamic_cast<ColumnIdentifierNode * > (attr->getNext())) {
		t->AddAttribute(attr->name(), (attr->getDataType()));
	}
	
	ErrorCode er = SchemaManager::AddTable(t);
	
	delete t;

	return er;
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