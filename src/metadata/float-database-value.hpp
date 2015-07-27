#ifndef FLOAT_DATABASE_VALUE_HPP_
#define FLOAT_DATABASE_VALUE_HPP_

#include "metadata\database-value.hpp"

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

#endif