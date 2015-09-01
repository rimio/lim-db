#include "schema\attribute.hpp"

Attribute::~Attribute() {
};

Attribute::Attribute(DataType type, std::string name, INT32 position) {
	type_ = type;
	name_ = name;
	position_ = position;
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