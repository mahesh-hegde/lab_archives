identifier [a-zA-Z_][a-zA-Z0-9_]*

%{
	#include <stdio.h>
	#include <stdlib.h>
	int sf = 0, pf = 0;
%}

%%

"scanf" {
	sf++;
	fprintf(yyout, "readf");
}

"printf" {
	pf++;
	fprintf(yyout, "writef");
}

{identifier} fprintf(yyout, "%s", yytext);

%%
int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "usage: %s input_file output_file", argv[0]);
		exit(1);
	}
	yyin = fopen(argv[1], "r");
	yyout = fopen(argv[2], "w");
	yylex();
	printf("Number of Scanfs=%d\nNumber of Printf's=%d\n", sf, pf);
	return 0;
}

