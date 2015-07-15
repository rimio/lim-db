#include "base\serialize.hpp"

#include <vector>

Serialize::Serialize(BYTE* starting_pointer_, Table *t) {
	var_index_ = 0;
	offset_4bytes_ = 0;
	offset_8bytes_ = 0;
	total_offset_4bytes_ = 0;
	total_offset_8bytes_ = 0;
	total_var_index_ = 0;

	starting_pointer_ = starting_pointer_;
	std::vector<Attribute> at = t->get_table_attributes();
	
	for (std::vector<Attribute>::iterator it = at.begin(); it != at.end(); ++it) {
		if ((*it).get_type() == DB_INTEGER) total_offset_4bytes_++;
		else if ((*it).get_type() == DB_FLOAT) total_offset_8bytes_++;
		else total_var_index_++;
	}
}

//Assignes the desired value at the chosen starting pointer ignoring the two dummy variables, the space for offsets, and the other integers already stored
INT32 Serialize::IntSerialize(INT32 value) {
	*(starting_pointer_ + 8 + (total_var_index_ * 4) + (offset_4bytes_ * 4) ) = value;
	offset_4bytes_++;
	return offset_4bytes_;
}
//Assignes the desired value at the chosen starting pointer ignoring the two dummy variables, the space for offsets, the space for integers and the other flaots already stored
INT32 Serialize::FloatSerialize(float value) {
	*(starting_pointer_ + 8 + (total_var_index_ * 4) + (total_offset_4bytes_*4) + (offset_8bytes_*8)) = value;
	offset_8bytes_++;
	return offset_8bytes_;
}
INT32 Serialize::StringSerialize(std::string value) {
	//First, skip dummy variables, offsets and other fixed_sized variables already stored
	INT32 size_before_string = 8 + (total_var_index_ * 4) + (total_offset_4bytes_ * 4) + (total_offset_8bytes_ * 8);
	//pointer to the first offset value
	BYTE * read_sizes = starting_pointer_ + 8;
	//for each offset value, read the size stored there
	for (int i = 1; i <= var_index_; ++i){
		INT32 size = *(read_sizes);
		//Skip the already stored string
		size_before_string += size;
		//Go to next offset
		read_sizes += 4;
	}
	
	*(starting_pointer_ + size_before_string) = (BYTE)value.c_str();

	var_index_++;
	return var_index_;
}

INT32 Serialize::IntDeserialize(INT32 int_number){
	return *(starting_pointer_ + 8 + 4 * (int_number - 1));
}

float Serialize::FloatDeserialize(INT32 float_number){
	return *(starting_pointer_ + 8 + 4 * (total_offset_4bytes_)+8 * (float_number - 1));
}

std::string Serialize::StringDeserialize(INT32 string_number){
	int string_length = *(starting_pointer_ + 8 + 4 * (string_number - 1));
	BYTE* string_start = starting_pointer_;

	string_start += + 8 + (total_var_index_ * 4) + (total_offset_4bytes_ * 4) + (total_offset_8bytes_ * 8);
	//pointer to the first offset value
	BYTE * read_sizes = starting_pointer_ + 8;
	//for each offset value, read the size stored there
	for (int i = 1; i <string_number; ++i){
		INT32 size = *(read_sizes);
		//Skip the already stored string
		string_start += size;
		//Go to next offset
		read_sizes += 4;
	}

	std::string result = "";
	for (int i = 0; i < string_length; i++)
	{
		result += (char)(*(string_start + i));
	}
	return result;
}