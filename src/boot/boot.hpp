#ifndef BOOT_HPP_
#define BOOT_HPP_

#include "storage\sector-manager.hpp"

#define GET_SECTOR_MANAGER() Boot::get_sector_manager()

class Boot{
public:
	static SectorManager get_sector_manager();
	static void StartServer();
private:
	Boot(){};
	static SectorManager *sector_manager_;
};

#endif
