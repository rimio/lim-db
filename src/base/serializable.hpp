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
	static BYTE* SerializeInt(int arg, BYTE* ptr);
	//Serializes a float value at the location specified by *ptr
	static BYTE* SerializeFloat(float arg, BYTE* ptr);
	//Serializes a string at the location specified by *ptr
	static BYTE* SerializeString(std::string arg, BYTE* ptr);
	//Retreives an integer value fron the location specified by *ptr and moves the pointer forward
	static BYTE* DeserializeInt(BYTE *ptr, int *arg);
	//Retreives a float value from the location specified by *ptr and moves the pointer forward
	static BYTE* DeserializeFloat(BYTE *ptr, float *arg);
	//Retreives a string from the location specified by *ptr and moves the pointer forward
	static BYTE* DeserializeString(BYTE* ptr, std::string *arg);
};

#endif
