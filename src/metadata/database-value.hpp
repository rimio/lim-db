#ifndef DATABASE_VALUE_HPP_
#define DATABASE_VALUE_HPP_

#include "base\serializable.hpp"
#include "base\data-type.hpp"
#include "base\error-codes.hpp"
#include <string>
#include <cassert>

class DatabaseValue: public Serializable {
public:
	// Constructors
	DatabaseValue(int value) { value_.i = value; data_type_ = DB_INTEGER; need_clear_ = false; };
	DatabaseValue(float value) { value_.f = value; data_type_ = DB_FLOAT; need_clear_ = false; };
	DatabaseValue(std::string* value) { set_string_value(value, true); };
	DatabaseValue(bool value) { value_.b = value; data_type_ = DB_BOOLEAN; need_clear_ = false; };
	DatabaseValue(const DatabaseValue& value);
	DatabaseValue() { data_type_ = DB_UNKNOWN; need_clear_ = false; };

	~DatabaseValue();

	bool operator >(const DatabaseValue& value);
	bool operator <(const DatabaseValue& value);
	bool operator >=(const DatabaseValue& value);
	bool operator <=(const DatabaseValue& value);
	bool operator ==(const DatabaseValue& value);
	bool operator !=(const DatabaseValue& value);

	DatabaseValue& operator=(const DatabaseValue& value);
	DatabaseValue operator+(const DatabaseValue& value);
	DatabaseValue operator-(const DatabaseValue& value);
	DatabaseValue operator*(const DatabaseValue& value);
	DatabaseValue operator/(const DatabaseValue& value);
	DatabaseValue operator%(const DatabaseValue& value);
	// Getters
	INT32 int_value() { assert(data_type_ == DB_INTEGER); return value_.i; };
	float float_value() { assert(data_type_ == DB_FLOAT); return value_.f; };
	std::string string_value() { assert(data_type_ == DB_STRING); return (*value_.s); }
	bool bool_value() { assert(data_type_ == DB_BOOLEAN); return value_.b; };
	DataType get_type() { return data_type_; }

	// Setters
	void set_int_value (INT32 value);
	void set_float_value (float value);
	void set_string_value (std::string* value, bool copy);
	void set_bool_value (bool value);
	void set_type (DataType type) { data_type_ = type; }

	ErrorCode Cast (DataType type);
	ErrorCode Cast (DataType type, DatabaseValue *output);

	BYTE* Serialize(BYTE *ptr) override;
	BYTE* Deserialize(BYTE *ptr) override; 

	void Clone(const DatabaseValue& value);
	
	void set_need_clear() { need_clear_ = true; }
	void unset_need_clear() { need_clear_ = false; }
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