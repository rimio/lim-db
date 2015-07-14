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
	#include "parser/identifier-node.hpp"
	#include "parser/operator-node.hpp"
	#include "parser/value-node.hpp"

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
#include <vector>
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
	TypedParserNode *typed_parser_node;
	StatementNode *statement_node;
	CommandNode *command_node;
	ValueNode *value_node;
	OperatorNode *operator_node;
	TableIdentifierNode *table_identifier_node;
	ColumnIdentifierNode *column_identifier_node;
	IndexIdentifierNode *index_identifier_node;

	std::vector<ColumnIdentifierNode*> *column_identifier_node_list;
}

%token AND
%token COMMA					"','"
%token CREATE
%token DELETE
%token DOT						"dot"
%token DROP
%token END					0	"end of command"
%token EQUAL					"="
%token EXIT
%token FLOAT
%token FROM
%token GT						">"
%token GT_EQ					">="
%token INDEX
%token INSERT
%token INT
%token INTO
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
%token STRING
%token SLASH					"/"
%token STAR						"*"
%token TABLE
%token UPDATE
%token VALUES

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
%type <command_node>			command
%type <command_node>			exit_command

// Statements
%type <statement_node>			statement
%type <statement_node>			select_statement
%type <statement_node>			insert_statement
%type <statement_node>			delete_statement
%type <statement_node>			update_statement
%type <statement_node>			create_table_statement
%type <statement_node>			create_index_statement
%type <statement_node>			drop_table_statement
%type <statement_node>			drop_index_statement

// Typed nodes
%type <value_node>				literal
%type <typed_parser_node>		operand
%type <typed_parser_node>		expression
%type <typed_parser_node>		expression_list

// Identifiers
%type <table_identifier_node>	table_identifier
%type <table_identifier_node>	table_identifier_list
%type <column_identifier_node>	column_identifier
%type <index_identifier_node>	index_identifier

// Data definition language
%type <column_identifier_node>	column_definition
%type <column_identifier_node_list>	column_definition_list

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
	: SELECT expression_list FROM table_identifier_list
		{
			$$ = new SelectStatementNode ($2, $4);
			$$->setLocation (@1);
		}
	;

insert_statement
	: INSERT INTO table_identifier VALUES PAR_OPEN expression_list PAR_CLOSE
		{
			$$ = new InsertStatementNode ($3, $6);
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
	: CREATE TABLE table_identifier PAR_OPEN column_definition_list PAR_CLOSE
		{
			$$ = new CreateTableStatementNode ($3, $5);
			$$->setLocation (@1);
		}
	;

column_definition_list
	: column_definition_list COMMA column_definition 
		{
			$$ = $1;
			$$->push_back($3);
		}
	| column_definition
		{
			$$ = new std::vector <ColumnIdentifierNode*>;
			$$->push_back($1); 
		}
	;

column_definition
	: column_identifier INT
		{
			$$ = $1;
			$$->setDataType (DB_INTEGER);
		}
	| column_identifier FLOAT
		{
			$$ = $1;
			$$->setDataType (DB_FLOAT);
		}
	| column_identifier STRING
		{
			$$ = $1;
			$$->setDataType (DB_STRING);
		}
	;

create_index_statement
	: CREATE INDEX index_identifier
		{
			$$ = new CreateIndexStatementNode ();
			$$->setLocation (@1);
		}
	;

drop_table_statement
	: DROP TABLE table_identifier
		{
			$$ = new DropTableStatementNode ($3);
			$$->setLocation (@1);
		}
	;

drop_index_statement
	: DROP INDEX index_identifier
		{
			$$ = new DropIndexStatementNode ();
			$$->setLocation (@1);
		}
	;

expression_list
	: expression COMMA expression_list
		{
			$$ = $1;
			$$->setNext ($3);
		}
	| expression
		{
			$$ = $1;
		}
	;

expression
	: expression OR expression
		{
			$$ = new OrOperatorNode ($1, $3);
			$$->setLocation (@1);
		}
	| expression AND expression
		{
			$$ = new AndOperatorNode ($1, $3);
			$$->setLocation (@1);
		}
	| NOT expression
		{
			$$ = new NotOperatorNode ($2);
			$$->setLocation (@1);
		}
	| expression LT expression
		{	
			$$ = new LtOperatorNode ($1, $3);
			$$->setLocation (@1);
		}
	| expression LT_EQ expression
		{
			$$ = new LtEqOperatorNode ($1, $3);
			$$->setLocation (@1);
		}
	| expression GT expression
		{
			$$ = new GtOperatorNode ($1, $3);
			$$->setLocation (@1);
		}
	| expression GT_EQ expression
		{
			$$ = new GtEqOperatorNode ($1, $3);
			$$->setLocation (@1);
		}
	| expression EQUAL expression
		{
			$$ = new EqualOperatorNode ($1, $3);
			$$->setLocation (@1);
		}
	| expression NOT_EQUAL expression
		{
			$$ = new NotEqualOperatorNode ($1, $3);
			$$->setLocation (@1);
		}
	| expression PLUS expression
		{
			$$ = new PlusOperatorNode ($1, $3);
			$$->setLocation (@1);
		}
	| expression MINUS expression
		{
			$$ = new MinusOperatorNode ($1, $3);
			$$->setLocation (@1);
		}
	| expression STAR expression
		{
			$$ = new MultiplicationOperatorNode ($1, $3);
			$$->setLocation (@1);
		}
	| expression SLASH expression
		{
			$$ = new DivisionOperatorNode ($1, $3);
			$$->setLocation (@1);
		}
	| expression MODULO expression
		{
			$$ = new ModuloOperatorNode ($1, $3);
			$$->setLocation (@1);
		}
	| MINUS expression %prec NEGATION
		{
			$$ = new MinusOperatorNode ($2, nullptr);
			$$->setLocation (@1);

			// Check for chained negations
			if ($2->getNodeType () == PT_OPERATOR)
			{
				OperatorNode *opn = (OperatorNode *) $2;
				if (opn->getOperatorType () == PT_OPERATOR_MINUS)
				{
					MinusOperatorNode *mopn = (MinusOperatorNode *) opn;
					if (mopn->getRight () == nullptr)
					{
						error (@2, "chained negation not allowed");
					}
				}
			}
		}
	| PAR_OPEN expression PAR_CLOSE
		{
			// Allow paranthesis for any expression
			$$ = $2;
		}
	| operand
		{
			$$ = $1;
		}
	;

operand
	: literal
		{
			$$ = $1;
		}
	| column_identifier
		{
			$$ = $1;
		}
	;

literal
	: ILITERAL
		{
			$$ = new IntegerValueNode ($1);
			$$->setLocation (@1);
		}
	| FLITERAL
		{
			$$ = new FloatValueNode ($1);
			$$->setLocation (@1);
		}
	| SLITERAL
		{
			$$ = new StringValueNode (*($1));
			delete ($1);
			$$->setLocation (@1);
		}
	;

table_identifier_list
	: table_identifier COMMA table_identifier_list
		{
			$$ = $1;
			$$->setNext ($3);
		}
	| table_identifier
		{
			$$ = $1;
		}
	;

table_identifier
	: IDENTIFIER
		{
			$$ = new TableIdentifierNode (*($1));
			delete ($1);
			$$->setLocation (@1);
		}
	;

column_identifier
	: IDENTIFIER
		{
			$$ = new ColumnIdentifierNode (*($1));
			delete ($1);
			$$->setLocation (@1);
		}
	| IDENTIFIER DOT IDENTIFIER
		{
			$$ = new ColumnIdentifierNode (*($1), *($3));
			delete ($1);
			delete ($3);
			$$->setLocation (@1);
		}
	;

index_identifier
	: IDENTIFIER
		{
			$$ = new IndexIdentifierNode (*($1));
			delete ($1);
			$$->setLocation (@1);
		}
	| IDENTIFIER DOT IDENTIFIER
		{
			$$ = new IndexIdentifierNode (*($1), *($3));
			delete ($1);
			delete ($3);
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
