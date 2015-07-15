#include "base\generic-operations.hpp"
#include "schema\schema-manager.hpp"
#include "statement-node.hpp"

#include <map>

StatementNode::~StatementNode() {}

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

CreateTableStatementNode::~CreateTableStatementNode(){
	delete table_;
	while (!(*definition_).empty()) {
		ColumnIdentifierNode *it = (*definition_).back();
		(*definition_).pop_back();
		delete it;
	}
	(*definition_).clear();
}

std::string CreateTableStatementNode::print ()
{
	std::string s("CREATE TABLE ");
	s += table_ != nullptr ? table_->print() : "";
	s += std::string("(");
	for (std::vector<ColumnIdentifierNode*>::iterator attr = (*definition_).begin(); attr != (*definition_).end(); ++attr)
		s += (*attr)->name() + std::string(", ");
	s += std::string (")");
	return s;
}

ErrorCode CreateTableStatementNode::compile() {
	std::string table_name = table_->name();

	//Verify that the table name isn't already used
	if (GET_SCHEMA_MANAGER()->FindTable(table_name) != NULL)
		return ErrorManager::error(__HERE__, ER_TABLE_ALREADY_EXISTS, table_->name().c_str());
	
	//Lowercase all the attributes
	std::string attr_name;
	for (std::vector<ColumnIdentifierNode*>::iterator attr = (*definition_).begin(); attr != (*definition_).end(); ++attr) {
		attr_name = (*attr)->name();
		STRING_TO_LOWER(attr_name);
		(*attr) -> set_name( attr_name );
	}

	//Verify that all atrtribute names are different
	for (std::vector<ColumnIdentifierNode*>::iterator attr = (*definition_).begin(); attr != (*definition_).end(); ++attr) {
		for (std::vector<ColumnIdentifierNode*>::iterator attr2 = attr+1; attr2 != (*definition_).end(); ++attr2 ){
			if ((*attr)->name().compare((*attr2)->name()) == 0)
				return ErrorManager::error(__HERE__, ER_SAME_ATTRIBUTE, (*attr)->name().c_str());
		}
	}
	return NO_ERROR;
}
 
 ErrorCode CreateTableStatementNode::execute() {
	Table *t = new Table();

	t->set_table_name(table_->name()); 
	
	for (std::vector<ColumnIdentifierNode*>::iterator attr = (*definition_).begin(); attr != (*definition_).end(); ++attr) {
		t->AddAttribute((*attr)->name(), ((*attr)->getDataType()));
	}
	
	ErrorCode er = GET_SCHEMA_MANAGER()->AddTable(t);

	return er;
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
		+ (table_ != nullptr ? table_->print () : "");
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