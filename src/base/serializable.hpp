#ifndef SERIALIZABLE_HPP_
#define SERIALIZABLE_HPP_

#include "base\generic-constants.hpp"

#include <string>

class Serializable {
public:
	//Pure virtal functions
	virtual BYTE* Serialize(BYTE *ptr) = 0;
	virtual BYTE* Deserialize(BYTE *ptr) = 0;
	//Serializes an integer value at the location specified by *ptr
	static BYTE* SerializeInt(INT32 arg, BYTE* ptr);
	//Serializes a float value at the location specified by *ptr
	static BYTE* SerializeFloat(float arg, BYTE* ptr);
	//Serializes a string at the location specified by *ptr
	static BYTE* SerializeString(std::string arg, BYTE* ptr);
	//Retreives an integer value fron the location specified by *ptr and moves the pointer forward
	INT32 DeserializeInt(BYTE **ptr);
	//Retreives a float value from the location specified by *ptr and moves the pointer forward
	float DeserializeFloat(BYTE **ptr);
	//Retreives a string from the location specified by *ptr and moves the pointer forward
	std::string DeserializeString(BYTE** ptr);
};

#endif
