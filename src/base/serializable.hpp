#include "base\generic-constants.hpp"

#include <string>

class Serializable{
public:
	virtual BYTE* Serialize(BYTE *ptr) = 0;
};

class SerializeInt : Serializable {
	BYTE* Serialize(BYTE *ptr) override;
	static BYTE* SerializeArg(int arg, BYTE* ptr);
};

class SerializeFloat : Serializable {
	BYTE* Serialize(BYTE *ptr) override;
	static BYTE* SerializeArg(float arg, BYTE* ptr);
};