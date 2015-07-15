#include "base\generic-constants.hpp"

#include <string>

class Serializable{
public:
	virtual BYTE* Serialize(BYTE *ptr) = 0;
};

class SerializeInt : Serializable {
	BYTE* Serialize(BYTE *ptr) override;
};

class SerializeFloat : Serializable {
	BYTE* Serialize(BYTE *ptr) override;
};