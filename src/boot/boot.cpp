#include "boot\boot.hpp"

SectorManager * Boot::sector_manager_ = NULL;
SchemaManager * Boot::schema_manager_ = NULL;

void Boot::StartServer() {
	sector_manager_ = new SectorManager();
	schema_manager_ = new SchemaManager();
}

void Boot::StopServer() {
	delete sector_manager_;
	delete schema_manager_;
}

SectorManager* Boot::get_sector_manager() {
	return sector_manager_;
}

SchemaManager* Boot::get_schema_manager() {
	return schema_manager_;
}
