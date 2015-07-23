#include "metadata\database-value.hpp"

IntDatabaseValue::IntDatabaseValue(INT32 val) {
	value_ = val;
}

INT32 IntDatabaseValue::get_value() {
	return value_;
}

void IntDatabaseValue::set_value(INT32 value) {
	value_ = value;
}

BYTE* IntDatabaseValue::Serialize(BYTE *ptr) {
	return Serializable::SerializeInt(value_, ptr);
}

BYTE* IntDatabaseValue::Deserialize(BYTE *ptr) {
	return Serializable::DeserializeInt(ptr, &value_);
}

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
	return Serializable::DeserializeString(ptr,&value_);
}