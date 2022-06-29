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

%token IDENTIFIER INFIX POSTFIX PREFIX LITERAL FOR IF

%%
program:
	statement_set                 { printf("%d\n", $1); exit(0); }

for_statement:
	FOR '(' optexpr ';' optexpr ';' optexpr ')' block   { $$ = $9 + 1; }

block:
     	optexpr ';'         { $$ = 0; }
	| for_statement      { $$ = $1; }
	| '{' statement_set '}'      { $$ = $2; };

statement_set:
	 block statement_set { $$ = max($1, $2); }
	 |                   { $$ = 0; }
	 ;

expression:
	 operand INFIX expression
	 | POSTFIX IDENTIFIER
	 | IDENTIFIER POSTFIX
	 | operand
	 | '(' expression ')'
	 ;

optexpr:
	expression           {$$ = 0; }
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

