#include "parser\pt-drop-table.hpp"
#include "schema\table.hpp"
#include "schema\schema-manager.hpp"
#include "boot\boot.hpp"
#include "base\generic-operations.hpp"

PTDropTableRoot::~PTDropTableRoot () {
	delete table_;
}

// Compile conditions:
// 1. Table exists
ErrorCode PTDropTableRoot::Compile () {
	Table *tableSchema = NULL;
	std::string table_name;

	// We need lowercase table name
	table_name = table_->name ();
	STRING_TO_LOWER (table_name);
	table_->set_name (table_name);
	
	// Find table by name
	tableSchema = GET_SCHEMA_MANAGER ()->FindTable (table_->name());
	if (tableSchema == NULL) {
		// Not found
		return ErrorManager::error (__HERE__, ER_TABLE_DOES_NOT_EXIST,
									table_->name ());
	}

	// All good
	return NO_ERROR;
}

// Execute drop table
ErrorCode PTDropTableRoot::Execute () {
	return GET_SCHEMA_MANAGER ()->DropTable (table_->name ());
}

std::string PTDropTableRoot::Print () {
	assert (table_ != NULL);

	return
		std::string ("DROP TABLE")
		+ (table_ != NULL ? table_->name () : "(unknown)");
}