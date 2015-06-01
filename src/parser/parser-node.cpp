#include "parser/parser-node.hpp"

ParserNode::ParserNode ()
{
	next_ = nullptr;
	location_.begin.initialize(nullptr, 0, 0);
	location_.end.initialize(nullptr, 0, 0);
}

ParserNode::~ParserNode ()
{
	delete next_;
}

std::string ParserNode::printList (std::string sep)
{
	if (next_ != nullptr)
		return print () + sep + next_->printList (sep);
	else
		return print ();
}