%{
	#include<stdlib.h>
	#include "y.tab.h"
%}

identifier [a-zA-Z][A-Za-z0-9]*
infix [-+*/%=]|[><=]=?
postfix "++"|"--"
literal [0-9]+
for_keyword for
if_keyword if

/* For simplicity only some syntax is supported. */

%%
{for_keyword} return FOR;
{if_keyword} return IF;
{identifier} return IDENTIFIER;
{infix} return INFIX;
{postfix} return POSTFIX;
{literal} return LITERAL;
[(){};] return *yytext;
[ \n\t] ;
%%

int yywrap() { return 1; }

