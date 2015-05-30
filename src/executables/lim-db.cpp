#include <iostream>
#include <string>

#include "base/error-manager.hpp"
#include "parser/parser-context.hpp"

//
// Application initialization routine
//
ErrorCode Initialize ()
{
	// TODO
	return NO_ERROR;
}

//
// Application de-initialization routine
//
void Deinitialize ()
{
	// TODO
}

//
// Execute an internal command
//
ErrorCode ExecuteCommand (CommandNode& command, bool& shutdown)
{
	// Interpret command
	switch (command.getCommandType ())
	{
	case PT_COMMAND_EXIT:
		shutdown = true;
		break;

	default:
		return ErrorManager::error (__HERE__, ER_INVALID_PARSER_NODE);
	}
	
	// All ok
	return NO_ERROR;
}

//
// Input loop
//
ErrorCode InputLoop ()
{
	bool shutdown = false;
	
	while (!shutdown)
	{
		// Print prompt
		std::cout << std::endl << "lim-sql> ";

		// Read line from user
		std::string line;
		std::getline (std::cin, line);

		// Parse line
		ErrorCode rc = NO_ERROR;
		ParserContext context;
		rc = context.parseString (line);
		if (rc != NO_ERROR)
			continue;

		// Check we have a root node
		ParserNode *root = context.getRootNode ();
		if (root == nullptr)
		{
			ErrorManager::error (__HERE__, ER_MISSING_PARSER_NODE, "root");
			continue;
		}

		// TODO: Semantic checking
		
		// Execute statement or internal command
		switch (root->getNodeType ())
		{
		case PT_COMMAND:
			rc = ExecuteCommand (* ((CommandNode *)root), shutdown);
			break;

		case PT_STATEMENT:
			rc = NO_ERROR;
			break;

		default:
			ErrorManager::error (__HERE__, ER_INVALID_PARSER_NODE);
			continue;
		}
		
		// Check execution return code
		if (rc != NO_ERROR)
		{
			ErrorManager::error (__HERE__, ER_INVALID_PARSER_NODE);
			continue;
		}
	}
}

//
// Application entry point
//
int main (int argc, char **argv)
{
	ErrorCode rc = NO_ERROR;

	// TODO: Parse arguments
	
	// Application initialization
	rc = Initialize ();
	if (rc != NO_ERROR)
		goto exitpoint;
	
	// Input loop - process commands
	rc = InputLoop ();
	
	// Application de-initialization
	Deinitialize ();

exitpoint:
	return (rc == NO_ERROR ? 0 : -1);
}