#include "base\serializable.hpp"


BYTE* SerializeInt::Serialize(BYTE * ptr){
	return ptr + 4;
}