#include "parser/parser-context.hpp"

#include <sstream>

ParserContext::ParserContext ()
{
	lexer_ = nullptr;
	parser_ = nullptr;
}

ParserContext::~ParserContext ()
{
	// Free memory
	if (lexer_ != nullptr)
	{
		delete lexer_;
		lexer_ = nullptr;
	}
	if (parser_ != nullptr)
	{
		delete parser_;
		parser_ = nullptr;
	}
	// TODO: Free parse node tree
}

ErrorCode ParserContext::parseString (std::string& input)
{
	// Get stream from string
	std::istringstream sstr (input);
	
	// Allocate lexer
	if (lexer_ != nullptr)
		delete lexer_;
	lexer_ = new Lexer (&sstr);

	// Allocate parser
	if (parser_ != nullptr)
		delete parser_;
	parser_ = new Parser (*lexer_, *this, &root_node_);

	// Parse
	if (parser_->parse () != NO_ERROR)
	{
		return ErrorManager::error (__HERE__, ER_PARSING_FAILED);
	}

	// All ok
	return NO_ERROR;
}