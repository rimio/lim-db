#ifndef DATABASE_VALUE_HPP_
#define DATABASE_VALUE_HPP_

#include "base\serializable.hpp"
#include "base\data-type.hpp"
#include "base\error-codes.hpp"
#include <string>

class DatabaseValue: public Serializable {
public:
	// Constructors
	DatabaseValue(int value) { value_.i = value; data_type_ = DB_INTEGER; need_clear_ = false; };
	DatabaseValue(float value) { value_.f = value; data_type_ = DB_FLOAT; need_clear_ = false; };
	DatabaseValue(std::string* value) { value_.s = value; data_type_ = DB_STRING; need_clear_ = true; };
	DatabaseValue(bool value) { value_.b = value; data_type_ = DB_BOOLEAN; need_clear_ = false; };
	DatabaseValue() { data_type_ = DB_UNKNOWN; need_clear_ = false; };

	~DatabaseValue();

	bool operator >(const DatabaseValue& value);
	bool operator <(const DatabaseValue& value);
	bool operator >=(const DatabaseValue& value);
	bool operator <=(const DatabaseValue& value);
	bool operator ==(const DatabaseValue& value);

	// Getters
	INT32 int_value() { return value_.i; };
	float float_value() { return value_.f; };
	std::string string_value() { return (*value_.s); }
	bool bool_value() { return value_.b; };
	DataType get_type() { return data_type_; }

	// Setters
	void set_int_value (INT32 value);
	void set_float_value (float value);
	void set_string_value (std::string value);
	void set_bool_value (bool value);
	void set_type (DataType type) { data_type_ = type; }

	ErrorCode Cast (DataType type);
	ErrorCode Cast (DataType type, DatabaseValue *output);

	BYTE* Serialize(BYTE *ptr) override;
	BYTE* Deserialize(BYTE *ptr) override; 
private:
	int Compare(DatabaseValue arg);
	void ClearValue();
	bool need_clear_;
	DataType data_type_;
	union
	{
		INT32 i;
		float f;
		std::string *s;
		bool b;
	} value_;
};

#endif