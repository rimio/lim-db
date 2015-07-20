#include "base\serializable.hpp"


BYTE* SerializeInt::Serialize(BYTE * ptr){
	return ptr + 4;
}

BYTE* SerializeInt::SerializeArg(int arg, BYTE *storage_ptr){
	(*storage_ptr) = arg;
	return storage_ptr + 4;
}

BYTE* SerializeFloat::Serialize(BYTE * ptr){
	return ptr + 8;
}

BYTE* SerializeFloat::SerializeArg(float arg, BYTE *storage_ptr){
	(*storage_ptr) = arg;
	return storage_ptr + 8;
}
