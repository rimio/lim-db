#include "base\error-manager.hpp"
#include "base\generic-operations.hpp"
#include "boot\boot.hpp"
#include "schema\schema-manager.hpp"


#include <algorithm>
#include <utility>

std::map<std::string, Table*> SchemaManager::list_of_tables_;

bool SchemaManager::add_table(Table *t){
	TableID *id;
	ErrorCode er = NO_ERROR;
	er = GET_SECTOR_MANAGER().allocate_sector(id);
	if (er == NO_ERROR) {
		t->set_table_id(*id);
		list_of_tables_.insert(std::pair<std::string, Table*>(t->get_table_name(), t));
		return true;
	}
	else {
		return false;
	}
}

bool SchemaManager::drop_table(std::string table_name) {
	std::transform(table_name.begin(), table_name.end(), table_name.begin(), ::tolower);
	if (list_of_tables_.erase(table_name))
		return true;
	return false;
}

Table * SchemaManager::find_table(std::string table_name) {
	string_to_lower(table_name);
	if (list_of_tables_.find(table_name) != list_of_tables_.end())
		return list_of_tables_.find(table_name)->second;
	return NULL;
}