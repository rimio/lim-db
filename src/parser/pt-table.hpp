#ifndef PT_TABLE_HPP_
#define PT_TABLE_HPP_

#include "parser\parser-node.hpp"
#include "schema\table.hpp"

// Parse-tree node containing data about a database table
class PTTableNode : public virtual ParserNode {
public:
	PTTableNode (std::string name);

	std::string ToString ();

	// Accessors
	// TODO: Is it better to use pointers/references?
	std::string name () { return name_; };
	void set_name (std::string name) { name_ = name; };

private:
	PTTableNode ();

	// Members
	std::string name_;

	// Future implementation
	std::string alias_;
	Table* table_;
};
#endif // PT_TABLE_HPP_