#include "metadata\database-value.hpp"

void DatabaseValue::set_int_value(INT32 value) {
	if (data_type_ == DB_STRING)
		delete value_.s;
	data_type_ = DB_INTEGER;
	value_.i = value;
}

void DatabaseValue::set_float_value(float value) {
	if (data_type_ == DB_STRING)
		delete value_.s;
	data_type_ = DB_FLOAT;
	value_.f = value;
}

void DatabaseValue::set_string_value(std::string value) {
	data_type_ = DB_STRING;
	(*value_.s) = value;
}

void DatabaseValue::set_bool_value(bool value) {
	if (data_type_ == DB_STRING)
		delete value_.s;
	data_type_ = DB_BOOLEAN;
	value_.b = value;
}

BYTE* DatabaseValue::IntSerialize(BYTE* ptr) {
	return Serializable::SerializeInt(value_.i, ptr);
}

BYTE* DatabaseValue::IntDeserialize(BYTE* ptr) {
	data_type_ = DB_INTEGER;
	return Serializable::DeserializeInt(ptr, &value_.i);
}

BYTE* DatabaseValue::FloatSerialize(BYTE* ptr) {
	return Serializable::SerializeFloat(value_.f, ptr);
}

BYTE* DatabaseValue::FloatDeserialize(BYTE* ptr) {
	data_type_ = DB_FLOAT;
	return Serializable::DeserializeFloat(ptr, &value_.f);
}

BYTE* DatabaseValue::StringSerialize(BYTE* ptr) {
	return Serializable::SerializeString((*value_.s), ptr);
}

BYTE* DatabaseValue::StringDeserialize(BYTE* ptr) {
	data_type_ = DB_STRING;
	return Serializable::DeserializeString(ptr, value_.s);
}

BYTE* DatabaseValue::BoolSerialize(BYTE* ptr) {
	if (value_.b)
		return Serializable::SerializeInt(1, ptr);
	return Serializable::SerializeInt(0, ptr);
}

BYTE* DatabaseValue::BoolDeserialize(BYTE* ptr) {
	data_type_ = DB_BOOLEAN;

	INT32 val;

	BYTE* new_ptr = Serializable::DeserializeInt(ptr, &val);

	value_.b = (val == 1) ? true : false;

	return new_ptr;
}