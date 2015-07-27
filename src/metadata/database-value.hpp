#ifndef DATABASE_VALUE_HPP_
#define DATABASE_VALUE_HPP_

#include "base\serializable.hpp"
#include "base\data-type.hpp"

class DatabaseValue: public Serializable {
public:
	//Pure virtual functions
	virtual DataType get_type() = 0;
};

#endif