%{
	#include <string.h>
	#include <stdlib.h>

	#include "symbol.h"
	#define YYSTYPE Symbol
	#include "y.tab.h"
%}

NUMBER [0-9]+
LETTER [a-z]
NAME [a-zA-Z_][a-zA-Z0-9_]*
/* single letter variable names to simplify registers */

%%

{NUMBER} {
	yylval.tag = SYM_NUMBER;
	yylval.content.number = atol(yytext);
	return NUMBER;
}

{LETTER} {
	yylval.tag = SYM_CHAR;
	yylval.content.ch = yytext[0];
	return LETTER;
}

{NAME} {
	printf("Multi letter variable names not allowed.\n");
	exit(1);
}

[ \t\n] ;

. {return yytext[0];}

%%

