#ifndef PARSER_INDEX_HPP_
#define PARSER_INDEX_HPP_

#include "parser\parser-node.hpp"
#include "schema\table.hpp"

// Parse-tree node containing data about a database table
class ParserIndex : public virtual ParserNode {
public:
	ParserIndex (std::string name);

	std::string ToString ();

	// Accessors
	// TODO: Is it better to use pointers/references?
	std::string name () { return name_; };
	void set_name (std::string name) { name_ = name; };

private:
	ParserIndex ();

	// Members
	std::string name_;

	// Future implementation
	Table* table_;
};
#endif // PARSER_INDEX_HPP_