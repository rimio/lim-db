#ifndef PARSER_EXPRESSION_HPP_
#define PARSER_EXPRESSION_HPP_

#include "parser/parser-node.hpp"

//
// Base operator node
//
class ParserExpression : public ParserNode {
	
public:
	// Override virtual functions from ParserNode
	
	std::vector<ParserNode *>* arguments(){ return arguments_; }
protected:
	ParserExpression (std::vector<ParserNode*>* arguments);
	virtual ~ParserExpression ();

	void GetChildren(std::vector<ParserNode*>* children);

	// Inaccessible default constructor
	ParserExpression () { };

	// Members
	std::vector<ParserNode *>* arguments_;
};

#endif // PARSER_EXPRESSION_HPP_