#ifndef PARSER_EXPRESSION_HPP_
#define PARSER_EXPRESSION_HPP_

#include "parser/parser-node.hpp"

//
// Base operator node
//
class ParserExpression : public ParserNode {
	
protected:
	ParserExpression (std::vector<ParserNode*>* arguments);
	~ParserExpression ();

	// Override virtual functions from ParserNode
	void GetChildren (std::vector<ParserNode*>* children);

	// Inaccessible default constructor
	ParserExpression () { };

	// Members
	std::vector<ParserNode *>* arguments_;
};

#endif // PARSER_EXPRESSION_HPP_