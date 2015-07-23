#ifndef DATABASE_VALUE_HPP_
#define DATABASE_VALUE_HPP_

#include "base\serializable.hpp"
#include "base\data-type.hpp"

class DatabaseValue: public Serializable {
public:
	//Pure virtual functions
	virtual DataType get_type() = 0;
};

class IntDatabaseValue : public DatabaseValue {
public:
	//Constructors
	IntDatabaseValue() {};
	IntDatabaseValue(INT32 val);
	//Destructor
	~IntDatabaseValue(){};
	
	//Serializes the integer specified by value_ at the location of *ptr 
	//Pointer is moved forward
	BYTE* Serialize(BYTE *ptr) override;
	//value_ receives the deserialized integer from the location of *ptr  
	//Pointer is moved forward
	BYTE* Deserialize(BYTE *ptr) override;
	
	INT32 get_value();
	void set_value(INT32 value);
	DataType get_type() override { return DB_INTEGER; };
private:
	INT32 value_;
};

class FloatDatabaseValue : public DatabaseValue {
public:
	//Constructors
	FloatDatabaseValue() {};
	FloatDatabaseValue(float val);
	//Destructor
	~FloatDatabaseValue(){};

	//Serializes the float specified by value_ at the location of *ptr 
	//Pointer is moved forward
	BYTE* Serialize(BYTE *ptr) override;
	//value_ receives the deserialized float from the location of *ptr  
	//Pointer is moved forward
	BYTE* Deserialize(BYTE *ptr) override;
	
	float get_value();
	void set_value(float value);
	DataType get_type() override { return DB_FLOAT; };
private:
	float value_;
};

class StringDatabaseValue : public DatabaseValue {
public:
	//Constructors
	StringDatabaseValue() {};
	StringDatabaseValue(std::string val);
	//Destructor
	~StringDatabaseValue();

	//Serializes the string specified by value_ at the specified location 
	//Pointer is moved forward
	BYTE* Serialize(BYTE *ptr) override;
	//value_ receives the deserialized string from the location of *ptr  
	//Pointer is moved forward
	BYTE* Deserialize(BYTE *ptr) override;
	
	std::string get_value();
	void set_value(std::string value);
	DataType get_type() override { return DB_STRING; };
private:
	std::string value_;
};

#endif