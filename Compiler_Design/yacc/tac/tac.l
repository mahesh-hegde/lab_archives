%{
	#include <string.h>
	#include <stdlib.h>

	#include "symbol.h"
	#define YYSTYPE Symbol
	#include "y.tab.h"
%}

NUMBER [0-9]+
LETTER [a-zA-Z_][a-zA-Z0-9_]*

%%

{NUMBER} {
	yylval.tag = SYM_NUMBER;
	yylval.content.number = atol(yytext);
	return NUMBER;
}

{LETTER} {
	yylval.tag = SYM_NAME;
	yylval.content.name = strdup(yytext);
	return LETTER;
}

[ \t\n] ;

. {return yytext[0];}

%%

