#ifndef ATTRIBUTE_HPP_
#define ATTRIBUTE_HPP_

#include "base\data-type.hpp"
#include "base\generic-constants.hpp"
#include <string>

typedef enum{
	FIXED,
	UNFIXED
} DataSize;

class Attribute
{
	public:
		Attribute(DataType type, std::string name, INT32 position);
		~Attribute();

		DataType get_type();
		std::string get_name();
		DataSize get_flag();
		INT32 get_position();

		void set_flag(DataSize flag);
		void set_position(INT32 pos);

	private:
		DataType type_;
		std::string name_;
		DataSize flag_;
		INT32 position_;
};
#endif // ATTRIBUTE_HPP_