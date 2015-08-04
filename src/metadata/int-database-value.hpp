#ifndef INT_DATABASE_VALUE_HPP_
#define INT_DATABASE_VALUE_HPP_

#include "metadata\database-value.hpp"

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

#endif