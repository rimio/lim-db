#include "table.hpp"

Table::Table ()
{
	id_ = 0;
	allocated_sectors_ = NULL;
}

Table::Table (SectorID sector_id)
{
	id_ = (TableID) sector_id;
	MemToTable ();
}

Table::~Table(){
	attributes_.clear(); 
	delete allocated_sectors_;
}

TableID Table::get_table_id() {
	return id_;
}

std::string Table::get_table_name(){
	return name_;
}

int Table::get_number_of_attributes(){
	return attributes_.size();
}

std::vector<Attribute> Table::get_table_attributes(){
	return attributes_;
}

void Table::set_table_id(int id) {
	id_ = id;
}

void Table::set_table_name(std::string table_name) {
	name_ = table_name;
}

void Table::AddAttribute(std::string attr_name, DataType attr_type) {
	attributes_.emplace_back(attr_type,attr_name);
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