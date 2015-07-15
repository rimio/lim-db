#ifndef ATTRIBUTE_HPP_
#define ATTRIBUTE_HPP_

#include "base\data-type.hpp"
#include <string>

typedef enum{
	FIXED,
	UNFIXED
} DataSize;

class Attribute
{
	public:
		Attribute(DataType type, std::string name);
		~Attribute();

		DataType get_type();
		std::string get_name();
		DataSize get_flag();

	private:
		DataType type_;
		std::string name_;
		DataSize flag_;
};
#endif // ATTRIBUTE_HPP_