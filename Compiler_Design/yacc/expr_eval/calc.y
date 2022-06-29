%{
#include<stdio.h>
#include<stdlib.h>
void yyerror(char *);
int yylex(void);
%}

%token INTEGER NEWLINE

// some versions of yacc (bison) give a warning without below line
// some don't recognize it, have to comment out.

// %name arith_expr

%%
program:
	prompt program
	| NEWLINE
	|
	;

prompt:
       expr	NEWLINE { printf("%d\n", $1); }

expr:
    expr '+' F	{ $$ = $1 + $3; }
    | expr '-' F	{ $$ = $1 - $3; }
    | F
    ;

F:
    F '*' INTEGER	{ $$ = $1 * $3; }
    | F '/' INTEGER	{ $$ = $1 / $3; }
    | '(' expr ')'      { $$ = $2; }
    | INTEGER
    ;
%%

void yyerror(char *s) {
	printf("%s\n", s);
}

int main() {
	yyparse();
	return 0;
}
