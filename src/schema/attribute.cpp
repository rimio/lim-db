#include "schema\attribute.hpp"

Attribute::~Attribute() {
};

Attribute::Attribute(DataType type, std::string name, INT32 position) {
	type_ = type;
	name_ = name;
	position_ = position;
}

DataType Attribute::get_type() {
	return type_;
}

std::string Attribute::get_name() {
	return name_;
}

INT32 Attribute::get_position() {
	return position_;
}

void Attribute::set_position(INT32 pos) {
	position_ = pos;
}

bool Attribute::isFixed() {
	if (type_ == DB_STRING)
		return false;
	else
		return true;
}