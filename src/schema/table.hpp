#ifndef TABLE_HPP_
#define TABLE_HPP_

#include "storage\sector.hpp"
#include "schema\attribute.hpp"
#include "metadata\sector-group.hpp"
#include "base\error-codes.hpp"
#include <string>
#include <vector>

typedef SectorID TableID;

class Table
{
private:

	TableID id_;

	std::string name_;

	SectorGroup* allocated_sectors_;

	int n_attributes_;

	Attribute *attributes_;

public:
	// Constructors
	Table ();
	Table (SectorID sector_id);

	ErrorCode TableToMem ();
	ErrorCode MemToTable ();

	TableID get_table_id();
	std::string get_table_name();
	int get_number_of_attributes();
	Attribute *get_table_attributes();

	void set_table_id(int id);
	void set_table_name(std::string table_name);
	void add_attribute(Attribute * table_attribute);
};
#endif // TABLE_HPP_