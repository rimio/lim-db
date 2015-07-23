#include "base\serializable.hpp"

BYTE* Serializable::SerializeInt(int arg, BYTE* ptr) {
	memcpy(ptr, &arg, sizeof(arg));
	return ptr + 4;
}

BYTE* Serializable::SerializeFloat(float arg, BYTE* ptr) {
	memcpy(ptr, &arg, sizeof(arg));
	return ptr + 8;
}

BYTE* Serializable::SerializeString(std::string arg, BYTE* ptr) {
	int length = arg.length();

	// Serialize the length of the string
	memcpy(ptr, &length, sizeof(length));
	ptr += 4;
	
	// Serialize the string
	memcpy(ptr, arg.c_str(), length);
	return ptr + length;
}

BYTE* Serializable::DeserializeInt(BYTE *ptr, int *arg) {
	memcpy(arg, ptr, sizeof(int));
	return ptr+4;
}

BYTE* Serializable::DeserializeFloat(BYTE *ptr, float *arg) {
	memcpy(arg, ptr, sizeof(float));
	return ptr+8;
}

BYTE* Serializable::DeserializeString(BYTE *ptr, std::string *arg){
	int length;
	// Deserialize the length of the string
	memcpy(&length, ptr, sizeof(int));
	ptr += 4;
	
	char * buffer = (char*)malloc((length+1)*sizeof(char));
	// Put the stirng intr an array of chars
	memcpy(buffer, ptr, length);
	buffer[length] = '\0';

	// Put the string into the std::string argument
	(*arg) += buffer;

	free(buffer);

	return ptr + length;
}