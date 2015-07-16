#include "base\generic-constants.hpp"

#include <string>

class Serializable {
public:
	virtual BYTE* SerializeInt(BYTE *ptr) = 0;
	virtual BYTE* SerializeFloat(BYTE *ptr) = 0;
	
private:
};