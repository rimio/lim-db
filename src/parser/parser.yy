%skeleton "lalr1.cc"
%require  "3.0"
%locations
%debug
%defines
%define parser_class_name {Parser}
%define parse.error verbose

%code requires
{
	/* Node includes */
	#include "parser/parser-node.hpp"
	#include "parser/command-node.hpp"
	#include "parser/statement-node.hpp"

	class ParserContext;
	class Lexer;
}

%lex-param		{ Lexer &lexer  }
%parse-param	{ Lexer &lexer  }
%lex-param		{ ParserContext &context }
%parse-param	{ ParserContext &context }
%parse-param	{ ParserNode **root_node }

%code
{

#include <iostream>
#include "base/error-manager.hpp"
#include "parser/parser-context.hpp"
#include "parser/lexer.hpp"

static int yylex (Parser::semantic_type *yylval, Parser::location_type *loc, Lexer &lexer, ParserContext &context);

}

%union {
	int ival;
	float fval;
	std::string *sval;

	ParserNode *parser_node;
	StatementNode *statement_node;
	CommandNode *command_node;
}

%token AND
%token COMMA					"','"
%token CREATE
%token DELETE
%token DROP
%token END					0	"end of file"
%token EQUAL					"="
%token EXIT
%token GT						">"
%token GT_EQ					">="
%token INDEX
%token INSERT
%token LT						"<"
%token LT_EQ					"<="
%token MINUS					"-"
%token MODULO					"MOD"
%token NOT
%token NOT_EQUAL				"!="
%token OR
%token PAR_CLOSE				")"
%token PAR_OPEN					"("
%token PLUS						"+"
%token SELECT
%token SEMICOLON				";"
%token SLASH					"/"
%token STAR						"*"
%token TABLE
%token UPDATE

/*
 * For SQL operator precedence, see T-SQL specs:
 * https://msdn.microsoft.com/en-us/library/ms190276.aspx
 */
%left OR
%left AND
%left NOT
%left LT LT_EQ GT GT_EQ EQUAL NOT_EQUAL
%left PLUS MINUS
%left STAR SLASH MODULO
%precedence NEGATION

%token <ival> ILITERAL			"integer literal"
%token <fval> FLITERAL			"float literal"
%token <sval> SLITERAL			"string literal"
%token <sval> IDENTIFIER		"identifier"

// Root rule
%type <parser_node>		statement_or_command

// Commands
%type <command_node>	command
%type <command_node>	exit_command

// Statements
%type <statement_node>	statement
%type <statement_node>	select_statement
%type <statement_node>	insert_statement
%type <statement_node>	delete_statement
%type <statement_node>	update_statement
%type <statement_node>	create_table_statement
%type <statement_node>	create_index_statement
%type <statement_node>	drop_table_statement
%type <statement_node>	drop_index_statement

%%

statement_or_command
	: statement optional_semicolon
		{
			*root_node = $1;
		}
	| command optional_semicolon
		{
			*root_node = $1;
		}

optional_semicolon
	: /* Nothing */
	| SEMICOLON
	;

command
	: exit_command
		{
			$$ = $1;
		}
	;

exit_command
	: EXIT
		{
			$$ = new ExitCommandNode ();
			$$->setLocation (@1);
		}
	;

statement
	: select_statement
		{
			$$ = $1;
		}
	| insert_statement
		{
			$$ = $1;
		}
	| delete_statement
		{
			$$ = $1;
		}
	| update_statement
		{
			$$ = $1;
		}
	| create_table_statement
		{
			$$ = $1;
		}
	| create_index_statement
		{
			$$ = $1;
		}
	| drop_table_statement
		{
			$$ = $1;
		}
	| drop_index_statement
		{
			$$ = $1;
		}
	;

select_statement
	: SELECT
		{
			$$ = new SelectStatementNode ();
			$$->setLocation (@1);
		}
	;

insert_statement
	: INSERT
		{
			$$ = new InsertStatementNode ();
			$$->setLocation (@1);
		}
	;

delete_statement
	: DELETE
		{
			$$ = new DeleteStatementNode ();
			$$->setLocation (@1);
		}
	;

update_statement
	: UPDATE
		{
			$$ = new UpdateStatementNode ();
			$$->setLocation (@1);
		}
	;

create_table_statement
	: CREATE TABLE
		{
			$$ = new CreateTableStatementNode ();
			$$->setLocation (@1);
		}
	;

create_index_statement
	: CREATE INDEX
		{
			$$ = new CreateIndexStatementNode ();
			$$->setLocation (@1);
		}
	;

drop_table_statement
	: DROP TABLE
		{
			$$ = new DropTableStatementNode ();
			$$->setLocation (@1);
		}
	;

drop_index_statement
	: DROP INDEX
		{
			$$ = new DropIndexStatementNode ();
			$$->setLocation (@1);
		}
	;

%%

void Parser::error (const Parser::location_type& loc, const std::string &err)
{
	ErrorManager::syntaxError (__HERE__, loc.begin.line, loc.begin.column, err);
}

static int yylex (Parser::semantic_type *yylval, Parser::location_type *loc, Lexer &lexer, ParserContext &context)
{
	int rc = lexer.yylex (yylval);
	*loc = lexer.getLocation ();
	return rc;
}
