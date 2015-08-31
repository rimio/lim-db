#include "table.hpp"

#include <cassert>

Table::Table ()
{
	id_ = 0;
	table_data_ = new TableData(name_);
	nr_float_= nr_int_ = nr_string_ = nr_attr_ = 0;
}

Table::Table (SectorID sector_id)
{
	id_ = (TableID) sector_id;
	table_data_ = new TableData(name_);
	nr_float_ = nr_int_ = nr_string_ = nr_attr_ = 0;
	MemToTable ();
}

Table::~Table() {
	attributes_.clear();
	delete table_data_;
}

TableID Table::table_id() {
	return id_;
}

std::string Table::table_name() {
	return name_;
}

int Table::number_of_attributes() {
	return attributes_.size();
}

std::vector<Attribute> Table::table_attributes() {
	return attributes_;
}

int Table::nr_string() {
	return nr_string_;
}

int Table::nr_float() {
	return nr_float_;
}

int Table::nr_int() {
	return nr_int_;
}

void Table::set_table_id(TableID id) {
	id_ = id;
}

void Table::set_table_name(std::string table_name) {
	name_ = table_name;
}

ErrorCode Table::AddAttribute(std::string attr_name, DataType attr_type) {
	nr_attr_++;
	
	attributes_.emplace_back(attr_type, attr_name, nr_attr_);
	
	switch (attr_type) {
	case DB_INTEGER:
		++nr_int_;
		break;
	case DB_FLOAT:
		++nr_float_;
		break;
	case DB_STRING:
		++nr_string_;
		break;
	default:
		assert(false);
		return ER_FAILED;
	}

	return NO_ERROR;
}

void Table::set_nr_string(int nr) {
	nr_string_ = nr;
}

void Table::set_nr_float(int nr) {
	nr_float_ = nr;
}

void Table::set_nr_int(int nr) {
	nr_int_ = nr;
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