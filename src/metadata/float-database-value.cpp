#include "metadata\float-database-value.hpp"

FloatDatabaseValue::FloatDatabaseValue(float val) {
	value_ = val;
}

float FloatDatabaseValue::get_value() {
	return value_;
}

void FloatDatabaseValue::set_value(float value) {
	value_ = value;
}

BYTE* FloatDatabaseValue::Serialize(BYTE *ptr) {
	return Serializable::SerializeFloat(value_, ptr);
}

BYTE* FloatDatabaseValue::Deserialize(BYTE *ptr) {
	return Serializable::DeserializeFloat(ptr, &value_);
}
