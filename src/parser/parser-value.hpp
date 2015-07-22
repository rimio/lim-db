#ifndef PARSER_VALUE_HPP_
#define PARSER_VALUE_HPP_

#include "parser/parser-node.hpp"

//
// Base class for all value nodes
//
class ParserValue : public ParserNode {
protected:
	// Hidden constructor
	ParserValue () { };
};

#endif // PARSER_VALUE_HPP_