#include "parser\pt-create-table.hpp"
#include "base\generic-operations.hpp"
#include "boot\boot.hpp"

PTCreateTableRoot::~PTCreateTableRoot () {
	delete table_;

	vector_clear_and_delete (*columns_);
	delete columns_;
}

std::string PTCreateTableRoot::Print () {
	std::string printed("CREATE TABLE ");

	printed += table_ != NULL ? table_->ToString () : "(unknown name)";
	printed += std::string("(");
	for (auto col = columns_->begin(); col != columns_->end(); ++col) {
		printed += (*col)->ToString () + std::string(", ");
	}
	printed += std::string(")");

	return printed;
}

ErrorCode PTCreateTableRoot::Compile () {
	std::string table_name = table_->name ();

	// Lower case name is needed
	STRING_TO_LOWER (table_name);
	table_->set_name(table_name);

	if (GET_SCHEMA_MANAGER ()->FindTable (table_name) != NULL) {
		return ErrorManager::error (__HERE__, ER_TABLE_ALREADY_EXISTS,
									table_->name ().c_str ());
	}

	// Set all columns names to lower case
	std::string attr_name;
	for (auto attr = columns_->begin (); attr != columns_->end (); ++attr) {
		attr_name = (*attr)->name ();
		STRING_TO_LOWER (attr_name);
		(*attr)->set_name (attr_name);
	}

	for (auto attr = columns_->begin (); attr != columns_->end (); ++attr) {
		for (auto attr2 = attr + 1; attr2 != columns_->end (); ++attr2) {
			if ((*attr)->name ().compare ((*attr2)->name ()) == 0)
				return ErrorManager::error (__HERE__, ER_SAME_ATTRIBUTE,
											(*attr)->name ().c_str ());
		}
	}

	return NO_ERROR;
}

ErrorCode PTCreateTableRoot::Execute () {

	// Create schema for table
	Table *t = new Table ();

	// Set table name
	t->set_table_name (table_->name ());

	// Add columns
	for (auto attr = columns_->begin (); attr != columns_->end (); ++attr) {
		t->AddAttribute ((*attr)->name (), (*attr)->data_type ());
	}

	// Add table schema
	return GET_SCHEMA_MANAGER ()->AddTable (t);
}