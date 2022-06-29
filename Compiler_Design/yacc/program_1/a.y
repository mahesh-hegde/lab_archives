%{
	#include <stdlib.h>
	int yylex(void);
	void yyerror(char *);
%}

%%

S: A B
;

A: 'a' A 'b'
|
;

B: 'b' B 'c'
|
;

%%

void yyerror(char *s) {
	printf("error: got %s\n", s);
	exit(1);
}

int main() {
	yyparse();
	printf("valid\n");
	return 0;
}

