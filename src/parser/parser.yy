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

	class ParserContext;
	class Lexer;
}

%lex-param		{ Lexer &lexer  }
%parse-param	{ Lexer &lexer  }

!!%lex-param		{ ParserContext &context }
!!%parse-param	{ ParserContext &context }

!!%parse-param	{ ParserNode **root_node }

%code
{

#include <iostream>
!!#include "error.h"
!!#include "parser-context.h"
#include "lexer.h"

static int yylex (Parser::semantic_type *yylval, Parser::location_type *loc, Lexer &lexer, ParserContext &context);

}

%union {
	int ival;
	float fval;
	std::string *sval;

	!!ParserNode *parser_node;
}

%token AND
%token COMMA					"','"
%token END					0	"end of file"
%token EQUAL					"="
%token GT						">"
%token GT_EQ					">="
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
%token SEMICOLON				";"
%token SLASH					"/"
%token STAR						"*"

/* For SQL operator precedence, see T-SQL specs:
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

!!%type <statement_node>	allocation_statement_part
!!%type <statement_node>	allocation_statement_part_list

/* this has dummy type */
%type <ival>			opt_newline

%%

%%

void Parser::error (const Parser::location_type& loc, const std::string &err)
{
	!!//Error::syntaxError (err, loc.begin.line, loc.begin.column);
}

static int yylex (Parser::semantic_type *yylval, Parser::location_type *loc, Lexer &lexer, ParserContext &context)
{
	int rc = lexer.yylex (yylval);
	*loc = lexer.getLocation ();
	return rc;
}
