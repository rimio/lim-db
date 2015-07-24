#ifndef PARSER_CONTEXT_HPP_
#define PARSER_CONTEXT_HPP_

#include "base/error-manager.hpp"
#include "parser/parser.hpp"
#include "parser/lexer.hpp"
#include "parser/parser-root.hpp"

#include <string>

class ParserContext
{
private:
	Parser *parser_;
	Lexer *lexer_;
	ParserRoot *root_node_;

public:
	ParserContext ();
	~ParserContext ();
	
	// Get the root node
	ParserRoot *getRootNode () const { return root_node_; }
	
	// Parse an input string.
	// This will do lexical analysis and syntax analysis.
	ErrorCode parseString (std::string& input);
};

#endif