#include "base\error-manager.hpp"
#include "base\generic-operations.hpp"
#include "boot\boot.hpp"
#include "schema\schema-manager.hpp"


#include <algorithm>
#include <utility>

std::map<std::string, Table*> SchemaManager::list_of_tables_;

SchemaManager::~SchemaManager(){
}

ErrorCode SchemaManager::AddTable(Table *t){
	
	TableID id;
	ErrorCode er = GET_SECTOR_MANAGER()->AllocateSector(&id);
	
	if (er == NO_ERROR) {
		t->set_table_id(id);
		list_of_tables_.insert(std::pair<std::string, Table*>(t->get_table_name(), t));
	}

	return er;
}

ErrorCode SchemaManager::DropTable(std::string table_name) {
	std::transform(table_name.begin(), table_name.end(), table_name.begin(), ::tolower);
	//Store a pointer to the desired table in order to completely delete it
	Table *t = list_of_tables_.find(table_name)->second;
	//Free the used sector
	ErrorCode er = GET_SECTOR_MANAGER()->DeallocateSector(t->get_table_id());
	if (er == NO_ERROR){
		//Delete the table from the list 
		list_of_tables_.erase(table_name);
		//Delete the table from memory 
		delete t;
	}
	return er;
}

Table * SchemaManager::FindTable(std::string table_name) {
	STRING_TO_LOWER(table_name);
	if (list_of_tables_.find(table_name) != list_of_tables_.end())
		return list_of_tables_.find(table_name)->second;
	return NULL;
}