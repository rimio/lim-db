#include "parser\pt-table.hpp"

PTTableNode::PTTableNode () {
	table_ = NULL;
}

PTTableNode::PTTableNode (std::string name) {
	PTTableNode ();

	name_ = name;
}

std::string PTTableNode::ToString () {
	return name_;
}