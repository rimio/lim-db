#include "parser\pt-insert.hpp"
#include "base\generic-operations.hpp"

//
// PTInsertNode
//

PTInsertNode::~PTInsertNode () {
	// delete table node
	delete table_;
	
	// delete column nodes
	vector_clear_and_delete (*columns_);
	delete columns_;

	// delete values lists
	for (auto value_list = values_->begin (); value_list != values_->end ();
		 ++value_list) {
		vector_clear_and_delete (**value_list);
	}
	vector_clear_and_delete (*values_);
	delete values_;
}

std::string PTInsertNode::ToString () {
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

//
// PTInsertRoot
//

PTInsertRoot::PTInsertRoot (PTTableNode* table,
							std::vector<PTColumnNode *>* columns,
							std::vector<std::vector<ParserNode *> *> *values,
							yy::location loc) {

	table_ = table;
	columns_ = columns;
	values_ = values;

	setLocation (loc);
}

ErrorCode PTInsertRoot::Compile () {
	return NO_ERROR;
}

ErrorCode PTInsertRoot::Prepare () {
	return NO_ERROR;
}

ErrorCode PTInsertRoot::Execute () {
	return NO_ERROR;
}

std::string PTInsertRoot::Print () {
	return ToString ();
}