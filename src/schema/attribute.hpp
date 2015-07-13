#ifndef ATTRIBUTE_HPP_
#define ATTRIBUTE_HPP_

#include "base\data-type.hpp"
#include <string>

class Attribute
{
	public:
		Attribute(DataType type, std::string name);
		~Attribute();

		DataType get_type();
		std::string get_name();
		
	private:
		DataType type_;
		std::string name_;
};
#endif // ATTRIBUTE_HPP_