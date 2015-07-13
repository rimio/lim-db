#include "boot\boot.hpp"

SectorManager * Boot::sector_manager_ = NULL;

Boot::~Boot(){
	delete sector_manager_;
}

void Boot::StartServer(){
	sector_manager_ = new SectorManager();
}

void Boot::CloseServer(){
	delete sector_manager_;
}

SectorManager* Boot::get_sector_manager(){
	return sector_manager_;
}


