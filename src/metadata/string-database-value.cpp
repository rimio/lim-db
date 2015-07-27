#include "metadata\string-database-value.hpp"

StringDatabaseValue::StringDatabaseValue(std::string val) {
	value_ = val;
}

std::string StringDatabaseValue::get_value() {
	return value_;
}

void StringDatabaseValue::set_value(std::string value) {
	value_ = value;
}

BYTE* StringDatabaseValue::Serialize(BYTE *ptr) {
	return Serializable::SerializeString(value_, ptr);
}

BYTE* StringDatabaseValue::Deserialize(BYTE *ptr) {
	value_.clear();
	return Serializable::DeserializeString(ptr, &value_);
}