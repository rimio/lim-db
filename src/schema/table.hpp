#ifndef TABLE_HPP_
#define TABLE_HPP_

#include "storage\sector.hpp"
#include "schema\attribute.hpp"
#include "metadata\file.hpp"
#include "base\error-codes.hpp"
#include <string>

typedef SectorID TableID;

class Table
{
private:

	TableID id_;

	std::string name_;

	File *file_;

	int n_attributes_;
	Attribute *attributes_;

public:
	Table ();
	Table (SectorID sector_id);

	ErrorCode TableToMem ();
	ErrorCode MemToTable ();
};
#endif // TABLE_HPP_