#include "class.hpp"

Table::Table ()
{
	id_ = 0;
	file_ = NULL;
	n_attributes_ = 0;
	attributes_ = NULL;
}

Table::Table (SectorID sector_id)
{
	id_ = (ClassID) sector_id;
	MemToClass ();
}

ErrorCode Table::TableToMem ()
{
	// TODO
	return ErrorCode::NO_ERROR;
}

ErrorCode Table::MemToTable ()
{
	// TODO
	return ErrorCode::NO_ERROR;
}