%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"

	int yylex();
	void yyerror(char *s);

	static inline int max(int a, int b) {
		return a > b ? a : b;
	}
%}

%token IDENTIFIER INFIX POSTFIX LITERAL FOR IF ELSE

// %name if_depth

%%
program:
	statement_set                 { printf("%d\n", $1); exit(0); }
	;

if_stmt:
	IF '(' expression ')' block { $$ = $5 + 1; }
	;

block:
     	optexpr ';'         { $$ = 0; }
	| if_stmt      { $$ = $1; }
	| '{' statement_set '}'      { $$ = $2; };

statement_set:
	 block statement_set { $$ = max($1, $2); }
	 |                   { $$ = 0; }
	 ;

expression:
	 operand INFIX expression
	 | operand
	 | POSTFIX IDENTIFIER
	 | IDENTIFIER POSTFIX
	 | '(' expression ')'
	 ;

optexpr:
	expression  { $$ = 0; }
	|
	;


operand:
         LITERAL
	 | IDENTIFIER
	 ;
%%

int main() {
	yyparse();
}

void yyerror(char *e) { puts(e); }

