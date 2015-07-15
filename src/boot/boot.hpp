#ifndef BOOT_HPP_
#define BOOT_HPP_

#include "storage\sector-manager.hpp"
#include "schema\schema-manager.hpp"
#include "base\serialize.hpp"

#define GET_SECTOR_MANAGER() Boot::get_sector_manager()
#define GET_SCHEMA_MANAGER() Boot::get_schema_manager()
#define GET_SERIALIZE() Boot::get_serialize()

class Boot{
public:
	//Retrieves the instance of the Sector Manager
	static SectorManager* get_sector_manager();
	//Retreives the instance of the Schema Manager
	static SchemaManager* get_schema_manager();
	//Retreives the instance of the Serialize class
	//static Serialize* get_serialize();
	//Generates the instance of Sector Manager
	static void StartServer();
	//Erases the instance of sector manager
	static void StopServer();
private:
	//Private constructor
	Boot(){};
	//Private destructor
	~Boot();
	static SectorManager *sector_manager_;
	static SchemaManager *schema_manager_;
	//static Serialize *serialize_;
};

#endif
