word [a-zA-Z0-9_]+
whitespace [ \t\n]

%{
	#include<string.h>
	int words = 0, chars = 0, whitespace = 0, lines = 1;

	// For color output
	#define COLOR_RED     "\x1b[31m"
	#define COLOR_RESET   "\x1b[0m"
%}

%%
{word}	{
	words++;
	chars += strlen(yytext);
}
{whitespace}	{
	whitespace++; // consider even newline as whitespace
	chars++;
	lines += *yytext == '\n';
}

[^a-zA-Z0-9_ \t\n]* {
	fprintf(stderr, COLOR_RED "==> unrecognized: %s\n" COLOR_RESET, yytext);
	chars += yyleng;
	// or strlen(yytext)
}
%%

int yywrap() { return 1; }

int main() {
	yylex();
	printf("\nwords=%d, chars=%d, whitespace=%d, lines=%d\n", words, chars, whitespace, lines);
	return 0;
}

