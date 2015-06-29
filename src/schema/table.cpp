#include "table.hpp"

Table::Table ()
{
	id_ = 0;
	allocated_sectors_ = NULL;
	n_attributes_ = 0;
	attributes_ = NULL;
}

Table::Table (SectorID sector_id)
{
	id_ = (TableID) sector_id;
	MemToTable ();
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