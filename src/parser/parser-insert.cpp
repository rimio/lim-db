#include "parser\parser-insert.hpp"
#include "base\generic-operations.hpp"
#include "boot\boot.hpp"
#include "parser\parser-value.hpp"

//
// PTInsertNode
//

ParserInsert::~ParserInsert() {
	// delete table node
	if (table_ != NULL)
		delete table_;

	// delete column nodes
	if (columns_ != NULL) {
		vector_clear_and_delete(*columns_);
		delete columns_;
	}

	// delete values lists
	if (values_ != NULL) {
		for (auto value_list = values_->begin(); value_list != values_->end();
			++value_list) {
			vector_clear_and_delete(**value_list);
		}
		vector_clear_and_delete(*values_);
		delete values_;
	}
}

std::string ParserInsert::ToString () {
	std::string to_string = std::string ("INSERT INTO ");
	bool first_value = false;

	to_string += table_->ToString ();

	// TODO: To add query case
	to_string += std::string (" VALUES ");

	for (auto values_list = values_->begin (); values_list != values_->end ();
		 ++values_list) {
		to_string += "(";

		first_value = true;
		for (auto value = (*values_list)->begin ();
			 value != (*values_list)->end (); ++value) {
			if (!first_value)
				to_string += ", ";
			first_value = false;
			to_string += (*value)->ToString ();
		}

		to_string += ")";
	}
	
	return to_string;
}

void ParserInsert::GetChildren (std::vector<ParserNode *>* children) {
	// Add table
	if (table_ != NULL)
		children->push_back (table_);

	// Add columns
	if (columns_ != NULL) {
		for (auto column = columns_->begin(); column != columns_->end (); ++column) {
			children->push_back (*column);
		}
	}

	// Add values
	if (values_ != NULL) {
		for (auto values_list = values_->begin ();
			 values_list != values_->end ();
			 ++values_list) {
			for (auto value = (*values_list)->begin ();
				 value != (*values_list)->end ();
				 ++value) {
				children->push_back (*value);
			}
		}
	}
}

//
// PTInsertRoot
//

ParserInsertStatement::ParserInsertStatement (ParserTable* table,
											  std::vector<ParserColumn *>* columns,
											  std::vector<std::vector<ParserNode *> *> *values,
											  yy::location loc) {

	table_ = table;
	columns_ = columns;
	values_ = values;

	setLocation (loc);
}

ErrorCode ParserInsert::NameResolvePre(NameResolveArg* arg, bool* stop_walk) {
	// Create new node
	std::vector <ParserTable *> new_node;

	// Add Parser table to the node
	(*arg).tables_stack_.push(new_node);

	return NO_ERROR;
}

ErrorCode ParserInsert::TypeCheckPre(TypeCheckArg* arg, bool* stop_walk) {
	std::vector < std::vector <std::vector <DataType>>> new_node;

	(*arg).tables_and_columns_stack_.push(new_node);

	return NO_ERROR;
}

ErrorCode ParserInsert::TypeCheckPost(TypeCheckArg* arg, bool* stop_walk) {
	std::vector<std::vector<DataType>> columns_types;
	
	columns_types = (*arg).tables_and_columns_stack_.top().back();

	for (auto val = (*values_).begin(); val != (*values_).end(); val++)
		for (int i = 0; i < (*(*val)).size(); i++) {
			std::vector<DataType> ctype = columns_types.at(i);
			
			if (ctype.at(0) == DB_ANY) continue;

			bool match = false;
			for (auto j :ctype) {
				if (j == static_cast <ParserValue*>((*(*val)).at(i))->value()->get_type())
					match = true;
			}
			if (!match)
				return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);
		}

	return NO_ERROR;
}

ErrorCode ParserInsert::CheckValues() {
	if (this->values_ == NULL) return NO_ERROR;
	
	// Make an insert instance, but without a table
	ParserInsert dummy_insert;

	dummy_insert.values_ = this->values_;
	
	//Should not return error if all values are propperly set
	ErrorCode er = dummy_insert.NameResolve();

	// Avoid destructing values
	dummy_insert.values_ = NULL;

	return er;

}

ErrorCode ParserInsertStatement::Compile () {
	// Check if table name exists
	Table *tableSchema = NULL;

	// Find table by name
	tableSchema = GET_SCHEMA_MANAGER()->FindTable(table_->name());
	if (tableSchema == NULL) {
		// Not found
		return ErrorManager::error(__HERE__, ER_TABLE_DOES_NOT_EXIST,
			table_->name().c_str());
	}

	table_->set_table(tableSchema);

	// Check no names in values
	ErrorCode er = CheckValues();

	// All good
	if (columns_ == NULL) {
		columns_ = new std::vector < ParserColumn * >();
		std::vector<Attribute> attributes = tableSchema->get_table_attributes();
		// Set all the columns 
		for (auto attr = attributes.begin(); attr != attributes.end(); ++attr) {
			(*columns_).push_back(new ParserColumn(attr->get_name(),
				attr->get_type(), table_->name(),table_));
		}
	}
	
	//Check column names exist in the referred table 
	std::vector<std::vector<ParserNode *> *>*v = values_;
	values_ = NULL;
	this->NameResolve();
	values_ = v;

	// Check the number of args in each tuple is corectly defined
	for (auto val = (*values_).begin(); val != (*values_).end(); val++) {
		if ((*(*val)).size() != (*columns_).size()) {
			return ErrorManager::error(__HERE__, ER_ATTR_AND_VALUES_DIFF_NUMBERS,
				table_->name().c_str());
		}
	}

	this->TypeCheck();

	return er;
}

ErrorCode ParserInsertStatement::Prepare () {
	return NO_ERROR;
}

ErrorCode ParserInsertStatement::Execute () {
	return NO_ERROR;
}

std::string ParserInsertStatement::Print () {
	return ToString ();
}