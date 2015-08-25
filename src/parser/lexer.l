%{

#include <string>
#include "base/error-manager.hpp"
#include "parser/lexer.hpp"

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

[Cc][Rr][Ee][Aa][Tt][Ee]		{ return Parser::token::CREATE; }
[Dd][Ee][Ll][Ee][Tt][Ee]		{ return Parser::token::DELETE; }
[Dd][Rr][Oo][Pp]				{ return Parser::token::DROP; }
[Ee][Xx][Ii][Tt]				{ return Parser::token::EXIT; }
[Ff][Ll][Oo][Aa][Tt]			{ return Parser::token::FLOAT; }
[Ff][Rr][Oo][Mm]				{ return Parser::token::FROM; }
[Ii][Nn][Dd][Ee][Xx]			{ return Parser::token::INDEX; }
[Ii][Nn][Ss][Ee][Rr][Tt]		{ return Parser::token::INSERT; }
[Ii][Nn][Tt]					{ return Parser::token::INT; }
[Ii][Nn][Tt][Oo]				{ return Parser::token::INTO; }
[Nn][Uu][Ll][Ll]				{ return Parser::token::NULLVAL; }
[Ss][Ee][Ll][Ee][Cc][Tt]		{ return Parser::token::SELECT; }
[Ss][Tt][Rr][Ii][Nn][Gg]		{ return Parser::token::STRING; }
[Tt][Aa][Bb][Ll][Ee]			{ return Parser::token::TABLE; }
[Uu][Pp][Dd][Aa][Tt][Ee]		{ return Parser::token::UPDATE; }
[Vv][Aa][Ll][Uu][Ee][Ss]		{ return Parser::token::VALUES; }

"("								{ return Parser::token::PAR_OPEN; }
")"								{ return Parser::token::PAR_CLOSE; }
","								{ return Parser::token::COMMA; }
";"								{ return Parser::token::SEMICOLON; }
[.]								{ return Parser::token::DOT; }

"+"								{ return Parser::token::PLUS; }
"-"								{ return Parser::token::MINUS; }
"*"								{ return Parser::token::STAR; }
"/"								{ return Parser::token::SLASH; }
"="								{ return Parser::token::EQUAL; }
"<"								{ return Parser::token::LT; }
"<="							{ return Parser::token::LT_EQ; }
">"								{ return Parser::token::GT; }
">="							{ return Parser::token::GT_EQ; }
"<>"							{ return Parser::token::NOT_EQUAL; }
[Mm][Oo][Dd]					{ return Parser::token::MODULO; }
[Nn][Oo][Tt]					{ return Parser::token::NOT; }
[Aa][Nn][Dd]					{ return Parser::token::AND; }
[Oo][Rr]						{ return Parser::token::OR; }

[0-9]+								{ yylval->ival = atoi (yytext); return Parser::token::ILITERAL; }
[0-9]*[.][0-9]+						{ yylval->fval = atof (yytext); return Parser::token::FLITERAL; }
[0-9]*[.][0-9]+[Ee][-]?[0-9]+		{ yylval->fval = atof (yytext); return Parser::token::FLITERAL; }
[0-9]+[Ee][-+]?[0-9]+				{ yylval->fval = atof (yytext); return Parser::token::FLITERAL; }
['][^']*[']							{
										std::string strq (yytext);
										yylval->sval = new std::string (strq.substr (1, strq.length () - 2));
										return Parser::token::SLITERAL;
									}
[a-zA-Z][a-zA-Z0-9]*			{ yylval->sval = new std::string (yytext); return Parser::token::IDENTIFIER; }

[ \t]							{ /* eat them */ location_.step (); }
[\n]+							{ location_.lines (yyleng); location_.step (); }

.								{ ErrorManager::syntaxError (__HERE__, location_.begin.line, location_.begin.column, "unrecognized token '" + std::string (yytext) + "'"); }

%%