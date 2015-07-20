#include "parser/parser-node.hpp"

ParserNode::ParserNode ()
{
	location_.begin.initialize(nullptr, 0, 0);
	location_.end.initialize(nullptr, 0, 0);
}

ParserNode::~ParserNode ()
{
}