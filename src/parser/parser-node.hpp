#ifndef PARSER_NODE_HPP_
#define PARSER_NODE_HPP_

#include "parser/location.hh"
#include "base/data-type.hpp"
#include "base/error-codes.hpp"

#include <vector>
#include <stack>

//
// Base class for all parser nodes
//

class ParserTable;

class ParserNode
{
public:
	// Virtual destructor
	virtual ~ParserNode ();

	// Location getter/setter
	yy::location getLocation () const { return location_; }
	void setLocation (yy::location loc) { location_ = loc; }

	virtual std::string ToString () { return std::string(""); };

protected:
	// Position in input buffer
	yy::location location_;
	
	// Hidden constructor
	ParserNode ();

	// Parse walk functions
	virtual void GetChildren (std::vector<ParserNode *>* children) = 0;
	

	class TypeCheckArg {
	};
	virtual ErrorCode TypeCheckPre (TypeCheckArg* arg, bool* stop_walk) = 0;
	virtual ErrorCode TypeCheckPost (TypeCheckArg* arg, bool* stop_walk) = 0;
	
	class NameResolveArg {
	public:
		std::stack<std::vector <ParserTable*>, std::vector < std::vector< ParserTable* > > > tables_stack_;
	};

	virtual ErrorCode NameResolvePre (NameResolveArg* arg, bool* stop_walk) = 0;
	virtual ErrorCode NameResolvePost (NameResolveArg* arg, bool* stop_walk) = 0;

	virtual ErrorCode ConstantFoldPost (void) = 0;

	ErrorCode NameResolve();
	ErrorCode TypeCheck();

private:
	template <class ArgPre, class ArgPost>
	ErrorCode ParserWalkInternal (ErrorCode (ParserNode::*pre_func) (ArgPre *, bool*), ArgPre* arg_pre,
								  ErrorCode (ParserNode::*post_func) (ArgPost *, bool*), ArgPost* arg_post,
								  bool* stop_walking);
	ErrorCode ParserWalkInternal (ErrorCode (ParserNode::*pre_func) (void), ErrorCode (ParserNode::*post_func) (void));

	template <class ArgPre, class ArgPost>
	ErrorCode ParserWalk(ErrorCode(ParserNode::*pre_func) (ArgPre *, bool*), ArgPre* arg_pre,
		ErrorCode(ParserNode::*post_func) (ArgPost *, bool*), ArgPost* arg_post);
	ErrorCode ParserWalk(ErrorCode(ParserNode::*pre_func) (void), ErrorCode(ParserNode::*post_func) (void));
};

#endif