#ifndef SCHEMA_MANAGER_HPP_
#define SCHEMA_MANAGER_HPP_

#include <string>
#include <map>
#include "base\error-codes.hpp"
#include "base\error-manager.hpp"
#include "schema/table.hpp"
#include "storage\sector-manager.hpp"

class SchemaManager { 
	public:
		//Destructor
		~SchemaManager();
		//Adds a new table
		static ErrorCode AddTable(Table *t);
		//Delets an existing table
		static bool DropTable(std::string table_name);
		//If there exists a table with the searched name, returns it, NULL otherwise
	    static Table* FindTable(std::string table_name);
	protected:
	private:
		static std::map<std::string, Table*> list_of_tables_;
};

#endif