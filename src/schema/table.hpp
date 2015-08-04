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

	std::vector<Attribute> attributes_;

	int nr_string_;

	int nr_float_;

	int nr_int_;

	int nr_attr_;

public:
	// Constructors
	Table();
	Table(SectorID sector_id);

	// Destructor
	~Table();

	ErrorCode TableToMem();
	ErrorCode MemToTable();

	TableID get_table_id();
	std::string get_table_name();
	int get_number_of_attributes();
	std::vector<Attribute> get_table_attributes();
	int get_nr_string();
	int get_nr_float();
	int get_nr_int();

	void set_table_id(TableID id);
	void set_table_name(std::string table_name);
	ErrorCode AddAttribute(std::string attr_name, DataType attr_type);
	void set_nr_string(int nr);
	void set_nr_float(int nr);
	void set_nr_int(int nr);
};
#endif // TABLE_HPP_