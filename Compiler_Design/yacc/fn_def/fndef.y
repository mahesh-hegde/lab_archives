%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"

	int yylex();
	void yyerror(const char *s);
%}

%token ID INFIX POSTFIX LITERAL

%%
prog: ID ID '(' param_list ')' '{' block '}'      { 
	printf("matched\n");
	exit(0);
}

param_list:
	param ',' param_list
	| param
	|
	;

param: ID ID
	 ;

block: stmt block
	 |
	 ;

stmt: expr ';'
	| ';'
	| ID ident_list ';'
	;

ident_list: ID
	| ID ',' ident_list
	;

expr:
	expr INFIX operand
	| POSTFIX ID
	| ID POSTFIX
	| operand
	| ID '(' expr_list ')'
	| '(' expr ')'
	;

expr_list:
	expr ',' expr_list
	| expr
	|
	;

operand: LITERAL | ID ;

%%

int main() {
	yyparse();
}

void yyerror(const char *s) { puts(s); }

