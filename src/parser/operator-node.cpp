#include "parser/operator-node.hpp"
#include <cassert>

std::string OperatorNode::print ()
{
	assert (left_ != nullptr);
	if (right_ == nullptr)
		return
			std::string ("(")
			+ toString ()
			+ std::string (" ")
			+ left_->print ()
			+ std::string (")");
	else
		return
			std::string ("(")
			+ left_->print ()
			+ std::string (" ")
			+ toString ()
			+ std::string (" ")
			+ right_->print ()
			+ std::string (")");
}