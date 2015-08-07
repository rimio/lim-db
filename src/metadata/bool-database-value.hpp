#ifndef BOOL_DATABASE_VALUE_HPP_
#define BOOL_DATABASE_VALUE_HPP_

#include "metadata\database-value.hpp"

class BoolDatabaseValue : public DatabaseValue {
public:
	//Constructors
	BoolDatabaseValue() {};
	BoolDatabaseValue(bool val);
	//Destructor
	~BoolDatabaseValue(){};

	//Serializes the boolean specified by value_ at the location of *ptr 
	//Pointer is moved forward
	BYTE* Serialize(BYTE *ptr) override;
	//value_ receives the deserialized boolean from the location of *ptr  
	//Pointer is moved forward
	BYTE* Deserialize(BYTE *ptr) override;

	bool get_value();
	void set_value(bool value);
	DataType get_type() override { return DB_BOOLEAN; };
private:
	bool value_;
};

#endif