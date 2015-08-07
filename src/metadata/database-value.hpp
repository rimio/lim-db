#ifndef DATABASE_VALUE_HPP_
#define DATABASE_VALUE_HPP_

#include "base\serializable.hpp"
#include "base\data-type.hpp"

#include <string>

class DatabaseValue: public Serializable {
public:
	// Constructors
	DatabaseValue(int value) { value_.i = value; data_type_ = DB_INTEGER; };
	DatabaseValue(float value) { value_.f = value; data_type_ = DB_FLOAT; };
	DatabaseValue(std::string* value) { value_.s = value; data_type_ = DB_STRING; };
	DatabaseValue(bool value) { value_.b = value; data_type_ = DB_BOOLEAN;};

	DataType get_type() { return data_type_; }

	// Getters
	INT32 int_value() { return value_.i; };
	float float_value() { return value_.f; };
	std::string string_value() { return (*value_.s); }
	bool bool_value() { return value_.b; };

	// Setters
	void set_int_value (INT32 value);
	void set_float_value (float value);
	void set_string_value (std::string value);
	void set_bool_value(bool value);

	BYTE* IntSerialize (BYTE *ptr);
	BYTE* IntDeserialize (BYTE *ptr);
	
	BYTE* FloatSerialize (BYTE *ptr);
	BYTE* FloatDeserialize (BYTE *ptr);
	
	BYTE* StringSerialize (BYTE *ptr);
	BYTE* StringDeserialize (BYTE *ptr);
	
	BYTE* BoolSerialize (BYTE *ptr);
	BYTE* BoolDeserialize (BYTE *ptr);

	BYTE* Serialize(BYTE *ptr) override { return ptr; };
	BYTE* Deserialize(BYTE *ptr) override{ return ptr; };
private:
	DataType data_type_;
	union Values 
	{
		INT32 i;
		float f;
		std::string *s;
		bool b;
	} value_;
};

#endif