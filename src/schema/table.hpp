#ifndef TABLE_HPP_
#define TABLE_HPP_

#include "storage\sector.hpp"
#include "schema\attribute.hpp"
#include "metadata\sector-group.hpp"
#include "base\error-codes.hpp"
#include <string>

typedef SectorID TableID;

class Table
{
private:

	TableID id_;

	std::string name_;

	SectorGroup* allocated_sectors_;

	int n_attributes_;
	Attribute* attributes_;

public:
	// Constructors
	Table ();
	Table (SectorID sector_id);

	ErrorCode TableToMem ();
	ErrorCode MemToTable ();
};
#endif // TABLE_HPP_