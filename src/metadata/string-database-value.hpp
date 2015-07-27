#ifndef STRING_DATABASE_VALUE_HPP_
#define STRING_DATABASE_VALUE_HPP_

#include "metadata\database-value.hpp"

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