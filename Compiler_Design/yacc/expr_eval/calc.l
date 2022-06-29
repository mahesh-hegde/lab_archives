%{
	#include<stdlib.h>
	#include "y.tab.h"
%}

%%
[0-9]+	{
	yylval = atoi(yytext);
	return INTEGER;
}

[-+*/()] return *yytext;

[ \t] ;

\n      return NEWLINE;

.       printf("unexpected: %s\n", yytext);
%%

