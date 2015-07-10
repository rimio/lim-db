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

TableID Table::get_table_id() {
	return id_;
}

std::string Table::get_table_name(){
	return name_;
}

int Table::get_number_of_attributes(){
	return n_attributes_;
}

Attribute* Table::get_table_attributes(){
	return attributes_;
}

void Table::set_table_id(int id) {
	id_ = id;
}

void Table::set_table_name(std::string table_name) {
	name_ = table_name;
}

void Table::add_attribute(Attribute * table_attribute) {
	attributes_[n_attributes_] = *table_attribute;
	++n_attributes_;
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