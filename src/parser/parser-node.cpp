#include "parser/parser-node.hpp"

ParserNode::ParserNode ()
{
	location_.begin.initialize(nullptr, 0, 0);
	location_.end.initialize(nullptr, 0, 0);
}

ParserNode::~ParserNode ()
{
}

// Walker on parse tree. It has a pre-walk function and post-walk function.
// Pre-walk function is called before advancing to node members.
// Post-walk function is called after advanced to node members.
// Walk can be halted with stop_walk argument.
template <class ArgPre, class ArgPost>
ErrorCode ParserNode::ParserWalk (ErrorCode (ParserNode::*pre_func) (ArgPre*, bool*), ArgPre* pre_arg,
								  ErrorCode (ParserNode::*post_func) (ArgPost*, bool*), ArgPost* post_arg) {
	bool stop_walk = false;
	return ParserWalkInternal (pre_func, pre_arg, post_func, post_arg, &stop_walk);
}

ErrorCode ParserNode::ParserWalk (ErrorCode (ParserNode::*pre_func) (void),
								  ErrorCode (ParserNode::*post_func) (void)) {
	return ParserWalkInternal (pre_func, post_func);
}

template <class ArgPre, class ArgPost>
ErrorCode ParserNode::ParserWalkInternal (ErrorCode (ParserNode::*pre_func) (ArgPre*, bool*), ArgPre* pre_arg,
										  ErrorCode (ParserNode::*post_func) (ArgPost*, bool*), ArgPost* post_arg,
										  bool* stop_walk) {
	ErrorCode error_code = NO_ERROR;
	std::vector<ParserNode *> children;

	error_code = (this->*pre_func) (pre_arg, stop_walk);
	if (error_code != NO_ERROR || *stop_walk)
		return error_code;

	GetChildren (&children);
	for (auto child = children.begin (); child != children.end (); ++child) {
		error_code = (*child)->ParserWalkInternal (pre_func, pre_arg, post_func, post_arg, stop_walk);
		if (error_code != NO_ERROR || *stop_walk)
			return error_code;
	}

	return (this->*post_func) (post_arg, stop_walk);
}

ErrorCode ParserNode::ParserWalkInternal (ErrorCode (ParserNode::*pre_func) (),
										  ErrorCode (ParserNode::*post_func) ()) {
	ErrorCode error_code = NO_ERROR;
	std::vector<ParserNode *> children;

	error_code = (this->*pre_func) ();
	if (error_code != NO_ERROR)
		return error_code;

	GetChildren (&children);
	for (auto child = children.begin (); child != children.end (); ++child) {
		error_code = (*child)->ParserWalkInternal (pre_func, post_func);
		if (error_code != NO_ERROR)
			return error_code;
	}

	return (this->*post_func) ();
}