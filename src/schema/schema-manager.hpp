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
		static bool add_table(Table *t);

		static bool drop_table(std::string table_name);

	    static Table find_table(std::string table_name);
	protected:
	private:
		static std::map<std::string, Table*> list_of_tables_;
};

#endif