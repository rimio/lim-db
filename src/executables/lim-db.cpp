#include <iostream>
#include <string>

#include "base/error-manager.hpp"
#include "parser/parser-context.hpp"
#include "boot\boot.hpp"

//
// Application initialization routine
//
ErrorCode Initialize ()
{
	// TODO
	Boot::StartServer();
	return NO_ERROR;
}

//
// Application de-initialization routine
//
void Deinitialize ()
{
	Boot::StopServer();
	// TODO
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
		ParserRoot *root = context.getRootNode ();
	
		if (root == nullptr)
		{
			ErrorManager::error (__HERE__, ER_MISSING_PARSER_NODE, "root");
			continue;
		}

		// DEBUG CODE: Print parse tree
		std::cout << std::endl << "statement: " << root->Print () << std::endl;

		// TODO: Semantic checking
		
		// Execute statement or internal command
		root->Process();

		// Delete parser resource for statement or internal command
		delete root;
		
		// Check execution return code
		if (rc != NO_ERROR)
		{
			ErrorManager::error (__HERE__, ER_INVALID_PARSER_NODE);
			continue;
		}
	}

	// All ok?

	return NO_ERROR;
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