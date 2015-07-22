#include "base\serializable.hpp"

BYTE* Serializable::SerializeInt(INT32 arg, BYTE* ptr) {
	INT32 *p = (INT32*)ptr;
	*p = arg;
	return ptr + 4;
}

BYTE* Serializable::SerializeFloat(float arg, BYTE* ptr) {
	float *p = (float*)ptr;
	*p = arg;
	return ptr + 8;
}

BYTE* Serializable::SerializeString(std::string arg, BYTE* ptr) {
	int length = arg.length();
	
	//Length increases by 1 because the equivalent in c of a string must end in a null-character '\0'
	char *s = new char[length+1];
	std::strcpy(s, arg.c_str());

	for (int i = 0; i <= length; i++) {
		*(ptr + i) = (BYTE)s[i];
	}

	return ptr + length + 1;
}

INT32 Serializable::DeserializeInt(BYTE** ptr) {
	*ptr += 4;
	return (int)(**ptr);
}

float Serializable::DeserializeFloat(BYTE** ptr) {
	*ptr += 8;
	return (float)(**ptr);
}

std::string Serializable::DeserializeString(BYTE** ptr){
	std::string result;
	char c = (char)(**ptr);
	
	while (c != '\0') {
		result += c;
		(*ptr)++;
		c = char(**ptr);
	}

	(*ptr)++;
	return result;
}