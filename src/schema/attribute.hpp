#ifndef ATTRIBUTE_HPP_
#define ATTRIBUTE_HPP_

#include "base\data-type.hpp"
#include "base\generic-constants.hpp"
#include <string>

class Attribute
{
	public:
		Attribute(DataType type, std::string name, INT32 position);
		~Attribute();

		DataType get_type();
		std::string get_name();
		INT32 get_position();

		void set_position(INT32 pos);
		bool isFixed();

	private:
		DataType type_;
		std::string name_;
		INT32 position_;
};
#endif // ATTRIBUTE_HPP_