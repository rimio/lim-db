#include "base\serializable.hpp"

BYTE* Serializable::SerializeInt(int arg, BYTE* ptr) {
	INT32 to_int32 = (INT32)arg;
	memcpy(ptr, &to_int32, sizeof(arg));
	return ptr + 4;
}

BYTE* Serializable::SerializeFloat(float arg, BYTE* ptr) {
	memcpy(ptr, &arg, sizeof(arg));
	return ptr + 8;
}

BYTE* Serializable::SerializeString(std::string arg, BYTE* ptr) {
	int length = arg.length();
	INT32 to_int32 = (INT32)length;
	
	// Serialize the length of the string
	memcpy(ptr, &to_int32, sizeof(length));
	ptr += 4;
	
	// Serialize the string
	memcpy(ptr, arg.c_str(), length);
	return ptr + length;
}

BYTE* Serializable::DeserializeInt(BYTE *ptr, int *arg) {
	INT32 from_int32;
	memcpy(&from_int32, ptr, sizeof(from_int32));
	*arg = (int)(from_int32);
	return ptr+4;
}

BYTE* Serializable::DeserializeFloat(BYTE *ptr, float *arg) {
	memcpy(arg, ptr, sizeof(float));
	return ptr+8;
}

BYTE* Serializable::DeserializeString(BYTE *ptr, std::string *arg){
	INT32 from_int32;
	// Deserialize the length of the string
	memcpy(&from_int32, ptr, sizeof(from_int32));
	int length = (int)(from_int32);
	ptr += 4;

	char * buffer = new char[length + 1];

	// Put the stirng intr an array of chars
	memcpy(buffer, ptr, length);
	buffer[length] = '\0';

	// Put the string into the std::string argument
	if (arg != nullptr) {
		(*arg) = buffer;
	}
	else {
		arg = new std::string(buffer);
	}

	delete buffer;

	return ptr + length;
}