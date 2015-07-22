#ifndef PARSER_COLUMN_HPP_
#define PARSER_COLUMN_HPP_

#include "parser\parser-node.hpp"
#include "base\data-type.hpp"

class ParserColumn : public virtual ParserNode {

public:
	// Ctors
	ParserColumn (std::string name) : name_ (name) {};

	std::string ToString ();

	// Accessors
	std::string name () { return name_; };
	void set_name (std::string name) { name_ = name; };

	std::string table_name () { return table_name_; }
	void set_table_name (std::string table_name) { table_name_ = table_name; };

	DataType data_type () { return data_type_; };
	void set_data_type (DataType data_type) { data_type_ = data_type; };

protected:
	ParserColumn () {};

private:

	// Column name
	std::string name_;

	// Column table name
	std::string table_name_;
	
	// Column data type
	DataType data_type_;
};

#endif // PARSER_COLUMN_HPP_