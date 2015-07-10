#include "schema\attribute.hpp"

Attribute::Attribute(DataType type, std::string name){
	type_ = type;
	name_ = name;
}

DataType Attribute::get_type(){
	return type_;
}

std::string Attribute::get_name(){
	return name_;
}