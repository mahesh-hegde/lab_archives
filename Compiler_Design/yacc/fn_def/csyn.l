%{
	#include<stdlib.h>
	#include "y.tab.h"
%}

identifier [a-zA-Z_][A-Za-z0-9_]*
infix [-+*/%=]|[><=]=?
postfix "++"|"--"
literal [0-9]+
strlit \"[^"]*\"

/* For simplicity only some syntax is supported. */

%%
{identifier} return ID;
{infix} return INFIX;
{postfix} return POSTFIX;
{literal}|{strlit} return LITERAL;
[(){};,] return *yytext;
[ \n\t] ;
%%

int yywrap() { return 1; }

