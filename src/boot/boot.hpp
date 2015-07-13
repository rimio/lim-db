#ifndef BOOT_HPP_
#define BOOT_HPP_

#include "storage\sector-manager.hpp"

#define GET_SECTOR_MANAGER() Boot::get_sector_manager()

class Boot{
public:
	//Retrieves the instance of the Sector Manager
	static SectorManager* get_sector_manager();
	//Generates the instance of Sector Manager
	static void StartServer();
	//Erases the instance of sector manager
	static void CloseServer();
	//Destructor
	~Boot();
private:
	//Private constructor
	Boot(){};
	static SectorManager *sector_manager_;
};

#endif
