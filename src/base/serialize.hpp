#include "base\generic-constants.hpp"
#include "schema\table.hpp"

#include <string>

class Serialize {
public:
	Serialize(BYTE* starting_pointer, Table *t);
	INT32 IntSerialize(INT32 value);
	INT32 IntDeserialize(INT32 int_number);
	INT32 FloatSerialize(float value);
	float FloatDeserialize(INT32 float_number);
	INT32 StringSerialize(std::string value);
	std::string StringDeserialize(INT32 string_number);

private:
	//How many string attributes
	INT32 total_var_index_;
	//How many int attributes 
	INT32 total_offset_4bytes_;
	//How many float attributes
	INT32 total_offset_8bytes_;
	//How many string attributes already used
	INT32 var_index_;
	//How many int attributes already used
	INT32 offset_4bytes_;
	//How many float attributes already used
	INT32 offset_8bytes_;
	BYTE* starting_pointer_;
};