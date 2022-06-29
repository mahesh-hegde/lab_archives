whitespace [ \t]*
sl_comment {whitespace}"//".*\n

/*
 * using regex only instead of keeping separate state
 * The theoretical disadvantage of this is that lexer needs to keep
   long multi-line comments in the buffer.
 * The theoretical advantage is you're saving the environment
   by writing less data sheet.
*/
ml_comment {whitespace}"/*"(([^*]*)|(\*+[^/]))*\*+"/"{whitespace}"\n"?

%{
	#include<stdlib.h>
	int sl = 0, ml = 0;
%}

%%
{sl_comment} sl++;
{ml_comment} ml++;
%%

int main(int argc, char **argv) {
	if (argc != 2 && argc != 3) {
		fprintf(stderr, "usage: %s input [output]\n", argv[0]);
		exit(1);
	}
	yyin = fopen(argv[1], "r");
	if (argc == 3) {
		yyout = fopen(argv[2], "w");
	}
	yylex();
	fprintf(stderr, "Single line comments: %d\n", sl);
	fprintf(stderr, "Multi line comments: %d\n", ml);
}
