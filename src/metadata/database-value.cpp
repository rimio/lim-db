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
	INT32 *p = (INT32*)ptr;
	*p = value_;
	return ptr + 4;
}

BYTE* IntDatabaseValue::Deserialize(BYTE *ptr) {
	INT32 *p = (INT32*)ptr;
	value_ = *p;
	return ptr + 4;
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
	float *p = (float*)ptr;
	*p = value_;
	return ptr + 8;
}

BYTE* FloatDatabaseValue::Deserialize(BYTE *ptr) {
	float *p = (float*)ptr;
	value_ = *p;
	return ptr + 8;
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
	int length = value_.length();

	//Length increases by 1 because the equivalent in c of a string must end in a null-character '\0'
	char *s = new char[length + 1];
	std::strcpy(s, value_.c_str());

	for (int i = 0; i <= length; i++) {
		*(ptr + i) = (BYTE)s[i];
	}

	return ptr + length + 1;
}

BYTE* StringDatabaseValue::Deserialize(BYTE *ptr) {
	value_.clear();
	char c = (char)(*ptr);

	while (c != '\0') {
		value_ += c;
		ptr++;
		c = (char)(*ptr);
	}

	ptr++;
	return ptr;
}