%{

#include <string>
#include "lexer.hpp"

#define yyterminate()	return Parser::token::END

%}

%option noyywrap
%option yyclass="Lexer"
%option c++

%{
#define YY_USER_ACTION location_.columns(yyleng);
%}

%%

%{
location_.step();
%}

"("								{ return Parser::token::PAR_OPEN; }
")"								{ return Parser::token::PAR_CLOSE; }

","								{ return Parser::token::COMMA; }
";"								{ return Parser::token::SEMICOLON; }

"+"								{ return Parser::token::PLUS; }
"-"								{ return Parser::token::MINUS; }
"*"								{ return Parser::token::STAR; }
"/"								{ return Parser::token::SLASH; }
"="								{ return Parser::token::EQUAL; }
"<"								{ return Parser::token::LT; }
"<="							{ return Parser::token::LT_EQ; }
">"								{ return Parser::token::GT; }
">="							{ return Parser::token::GT_EQ; }
"!="							{ return Parser::token::NOT_EQUAL; }

[Mm][Oo][Dd]					{ return Parser::token::MODULO; }
[Nn][Oo][Tt]					{ return Parser::token::NOT; }
[Aa][Nn][Dd]					{ return Parser::token::AND; }
[Oo][Rr]						{ return Parser::token::OR; }

[0-9]+								{ yylval->ival = atoi (yytext); return Parser::token::ILITERAL; }
[0-9]*[.][0-9]+						{ yylval->fval = atof (yytext); return Parser::token::FLITERAL; }
[0-9]*[.][0-9]+[Ee][-]?[0-9]+		{ yylval->fval = atof (yytext); return Parser::token::FLITERAL; }
[0-9]+[Ee][-]?[0-9]+				{ yylval->fval = atof (yytext); return Parser::token::FLITERAL; }
['][^']*[']							{
										std::string strq (yytext);
										yylval->sval = new std::string (strq.substr (1, strq.length () - 2));
										return Parser::token::SLITERAL;
									}
[a-zA-Z][a-zA-Z0-9.]*			{ yylval->sval = new std::string (yytext, strlen (yytext) - 1); return Parser::token::IDENTIFIER; }

[ \t]							{ /* eat them */ location_.step (); }
[\n]+							{ location_.lines (yyleng); location_.step (); }

.								{ /* Error::syntaxError ("unrecognized token '" + std::string (yytext) + "'", location_.begin.line, location_.begin.column); */ }

%%