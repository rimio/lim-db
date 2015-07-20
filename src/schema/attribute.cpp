#include "schema\attribute.hpp"

Attribute::~Attribute() {
};

Attribute::Attribute(DataType type, std::string name, INT32 position) {
	type_ = type;
	name_ = name;
	position_ = position;
	if (type == DB_STRING) 
		flag_ = UNFIXED;
	else flag_ = FIXED;
}

DataType Attribute::get_type() {
	return type_;
}

std::string Attribute::get_name() {
	return name_;
}

DataSize Attribute::get_flag() {
	return flag_;
}

INT32 Attribute::get_position() {
	return position_;
}

void Attribute::set_position(INT32 pos) {
	position_ = pos;
}

void Attribute::set_flag(DataSize flag) {
	flag_ = flag;
}