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
	#include "parser/parser-root.hpp"
	#include "parser/parser-node.hpp"
	#include "parser/parser-command.hpp"
	
	#include "parser/parser-column.hpp"
	#include "parser/parser-identifier.hpp"
	#include "parser/parser-table.hpp"
	#include "parser/parser-value.hpp"

	#include "parser/parser-alter-table.hpp"
	#include "parser/parser-create-table.hpp"
	#include "parser/parser-delete.hpp"
	#include "parser/parser-drop-table.hpp"
	#include "parser/parser-index.hpp"
	#include "parser/parser-insert.hpp"
	#include "parser/parser-select.hpp"
	#include "parser/parser-update.hpp"

	#include "parser/operator-node.hpp"

	#include <iostream>
	#include <vector>

	class ParserContext;
	class Lexer;
}

%lex-param		{ Lexer &lexer  }
%parse-param	{ Lexer &lexer  }
%lex-param		{ ParserContext &context }
%parse-param	{ ParserContext &context }
%parse-param	{ ParserRoot **root_node }

%code
{

#include "base/error-manager.hpp"
#include "parser/parser-context.hpp"
#include "parser/lexer.hpp"

static int yylex (Parser::semantic_type *yylval, Parser::location_type *loc, Lexer &lexer, ParserContext &context);

}

%union {
	int ival;
	float fval;
	std::string *sval;

	ParserRoot *parser_root_val;
	ParserNode *parser_node;
	TypedParserNode *typed_parser_node;
	ParserCommand *command_val;
	OperatorNode *operator_node;

	ParserIndex *index_node_val;
	ParserTable* table_node_val;
	ParserColumn* column_node_val;
	ParserValue* value_node_val;

	std::vector<ParserNode *>* parser_node_list;
	std::vector<ParserTable *>* table_node_list_val;
	std::vector<ParserColumn *>* column_node_list_val;
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
%type <command_val>			command
%type <command_val>			exit_command

// Statements
%type <parser_root_val>			statement
%type <parser_root_val>			select_statement
%type <parser_root_val>			insert_statement
%type <parser_root_val>			delete_statement
%type <parser_root_val>			update_statement
%type <parser_root_val>			create_table_statement
%type <parser_root_val>			create_index_statement
%type <parser_root_val>			drop_table_statement
%type <parser_root_val>			drop_index_statement

// Typed nodes
%type <value_node_val>			literal
%type <typed_parser_node>		operand
%type <typed_parser_node>		expression
%type <parser_node_list>		expression_list

// Identifiers
%type <table_node_val>	table_identifier
%type <table_node_list_val>	table_identifier_list
%type <column_node_val>	column_identifier
%type <index_node_val>	index_identifier

// Data definition language
%type <column_node_val>	column_definition
%type <column_node_list_val>	column_definition_list

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
			$$ = new ParserCommand (PT_COMMAND_EXIT);
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
	: SELECT expression_list FROM table_identifier
		{
			$$ = new ParserSelectStatement ($2, $4, @1);
		}
	;

insert_statement
	: INSERT INTO table_identifier VALUES PAR_OPEN expression_list PAR_CLOSE
		{
			std::vector<std::vector<ParserNode *> *> *values_list =
				new std::vector<std::vector<ParserNode *> *>;
			values_list->push_back ($6);

			$$ = new ParserInsertStatement ($3, NULL, values_list, @1);
		}
	;

delete_statement
	: DELETE
		{
			$$ = new ParserDeleteStatement (@1);
		}
	;

update_statement
	: UPDATE
		{
			$$ = new ParserUpdateStatement (@1);
		}
	;

create_table_statement
	: CREATE TABLE table_identifier PAR_OPEN column_definition_list PAR_CLOSE
		{
			$$ = new ParserCreateTableStatement ($3, $5, @1);
		}
	;

column_definition_list
	: column_definition_list COMMA column_definition 
		{
			$$ = $1;
			$$->push_back ($3);
		}
	| column_definition
		{
			$$ = new std::vector <ParserColumn *>;
			$$->push_back ($1); 
		}
	;

column_definition
	: column_identifier INT
		{
			$$ = $1;
			$$->set_data_type (DB_INTEGER);
		}
	| column_identifier FLOAT
		{
			$$ = $1;
			$$->set_data_type (DB_FLOAT);
		}
	| column_identifier STRING
		{
			$$ = $1;
			$$->set_data_type (DB_STRING);
		}
	;

create_index_statement
	: CREATE INDEX index_identifier
		{
			$$ = new ParserAlterTableStatement (@1);
		}
	;

drop_table_statement
	: DROP TABLE table_identifier
		{
			$$ = new ParserDropTableStatement ($3, @1);
		}
	;

drop_index_statement
	: DROP INDEX index_identifier
		{
			$$ = new ParserAlterTableStatement (@1);
		}
	;

expression_list
	: expression_list COMMA expression
		{
			$$ = $1;
			$$->push_back ($3);
		}
	| expression
		{
			$$ = new std::vector<ParserNode *>;
			$$->push_back ($1);
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
			//if ($2->getNodeType () == PT_OPERATOR)
			//{
				//OperatorNode *opn = (OperatorNode *) $2;
				//if (opn->getOperatorType () == PT_OPERATOR_MINUS)
				//{
					//MinusOperatorNode *mopn = (MinusOperatorNode *) opn;
					//if (mopn->getRight () == nullptr)
					//{
						//error (@2, "chained negation not allowed");
					//}
				//}
			//}
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
			// $$ = $1;
			$$ = NULL;
		}
	| column_identifier
		{
			// $$ = $1;
			$$ = NULL;
		}
	;

literal
	: ILITERAL
		{
			// TODO
			$$ = NULL;
		}
	| FLITERAL
		{
			// TODO
			$$ = NULL;
		}
	| SLITERAL
		{
			// TODO
			$$ = NULL;
		}
	;

table_identifier_list
	: table_identifier_list COMMA table_identifier
		{
			$$ = $1;
			$$->push_back ($3);
		}
	| table_identifier
		{
			$$ = new std::vector<ParserTable *>;
			$$->push_back ($1);
		}
	;

table_identifier
	: IDENTIFIER
		{
			$$ = new ParserTable (*($1));
			delete ($1);
			$$->setLocation (@1);
		}
	;

column_identifier
	: IDENTIFIER
		{
			$$ = new ParserColumn (*($1));
			delete ($1);
			$$->setLocation (@1);
		}
	| IDENTIFIER DOT IDENTIFIER
		{
			$$ = new ParserColumn (*($3));
			delete ($3);
			$$->set_table_name (*($1));
			delete ($1);
			$$->setLocation (@1);
		}
	;

index_identifier
	: IDENTIFIER
		{
			$$ = new ParserIndex (*($1));
			delete ($1);
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
