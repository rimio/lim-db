#ifndef FILE_HPP_
#define FILE_HPP_

#include "storage\sector.hpp"

class File
{
private:
	int n_sectors;
	SectorID *sectors;

public:
	File ();

	ErrorCode AppendSector ();
};
#endif // FILE_HPP_