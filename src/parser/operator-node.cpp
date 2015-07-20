#include "parser/operator-node.hpp"
#include <cassert>

std::string OperatorNode::ToString ()
{
	assert (left_ != nullptr);
	if (right_ == nullptr)
		return
			std::string ("(")
			+ ToString ()
			+ std::string (" ")
			+ left_->ToString ()
			+ std::string (")");
	else
		return
			std::string ("(")
			+ left_->ToString ()
			+ std::string (" ")
			+ ToString ()
			+ std::string (" ")
			+ right_->ToString ()
			+ std::string (")");
}