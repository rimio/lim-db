#include "parser\parser-select.hpp"
#include "base\generic-operations.hpp"
#include "boot\boot.hpp"
#include "storage\data-sector.hpp"
#include "storage\row-data.hpp"
#include "query-execution\query-execute-select.hpp"
#include "parser\parser-to-asl.hpp"
//
// PTSelectNode
//

ParserSelect::~ParserSelect () {
	// delete select list
	if (list_ != nullptr)
		vector_clear_and_delete (*list_);

	if (list_ != nullptr)
		delete list_;

	// delete from
	if (from_ != nullptr)
		delete from_;
}

std::string ParserSelect::ToString () {
	std::string to_string = std::string ("SELECT ");

	bool first_item = true;
	if (list_ != nullptr) {
		for (auto item = list_->begin (); item != list_->end (); ++item) {
			if (!first_item) {
				to_string += ", ";
			}
			first_item = false;

			to_string += (*item)->ToString ();
		}
	}

	to_string += "FROM ";
	to_string += from_->ToString ();

	return to_string;
}

void ParserSelect::GetChildren (std::vector<ParserNode *>* children) {
	// Add from_
	children->push_back(from_);

	// Add select list
	for (auto item = list_->begin (); item != list_->end (); ++item) {
		children->push_back (*item);
	}
}

//
// PTSelectRoot
//

ParserSelectStatement::ParserSelectStatement (std::vector<ParserNode *>* list,
											  ParserTable* from, yy::location loc) {

	list_ = list;
	from_ = from;

	setLocation (loc);
}

ErrorCode ParserSelect::NameResolvePre(NameResolveArg* arg, bool* stop_walk) {
	// Create new node
	std::vector <ParserTable *> new_node;

	// Add Parser table to the node
	arg->tables_stack_.push(new_node);
	arg->reference_to_list_ = list_;

	return NO_ERROR;
}

ErrorCode ParserSelectStatement::Compile () {
	// Check if table name exists
	Table *tableSchema = NULL;

	// Find table by name
	tableSchema = GET_SCHEMA_MANAGER()->FindTable(from_->name());
	if (tableSchema == NULL) {
		// Not found
		return ErrorManager::error(__HERE__, ER_TABLE_DOES_NOT_EXIST,
			from_->name().c_str());
	}

	from_->set_table(tableSchema);
	ErrorCode er = NO_ERROR;

	er = this->NameResolve();

	if (er != NO_ERROR)
		return er;

	return NO_ERROR;
}

ErrorCode ParserSelectStatement::Prepare () {
	return NO_ERROR;
}

ErrorCode ParserSelectStatement::Execute () {
	ErrorCode er = NO_ERROR;

	QueryExecuteSelect query = QueryExecuteSelect(from_, this);

	er = query.Execute();
	query.Print(values_);
	
	return NO_ERROR;
}

std::string ParserSelectStatement::Print () {
	return ToString ();
}

ErrorCode ParserSelect::ConstantFoldPost() {
	ErrorCode er = NO_ERROR;
	std::vector<DatabaseValue> row(list_->size(), DatabaseValue());
	int poz = values_.size();
	values_.push_back(row);
	
	for (int i = 0; i < list_->size(); i++) {
		if (list_->at(i)->computed_value().is_null()) continue;
		switch (list_->at(i)->computed_value().data_type()) {
		case DB_INTEGER:
			values_[poz][i].set_int_value(list_->at(i)->computed_value().int_value());
			break;
		case DB_FLOAT:
			values_[poz][i].set_float_value(list_->at(i)->computed_value().float_value());
			break;
		case DB_STRING:
			values_[poz][i].set_string_value(&(list_->at(i)->computed_value().string_value()), true);
			break;
		case DB_BOOLEAN:
			values_[poz][i].set_bool_value(list_->at(i)->computed_value().bool_value());
			break;
		default:
			return ER_FAILED;
		}
	}
	
	return er;
}