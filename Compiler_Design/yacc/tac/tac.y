// changes from 'official' program to support numbers & letters
// this program supports long numbers and variable names

%{
	#define YYSTYPE Symbol
	#include<stdio.h>
	#include<stdlib.h>

	#include "symbol.h"

	void print_sym(Symbol sym, const char *suffix);

	Symbol AddToTable(Symbol,Symbol,char);

	int yylex();
	void yyerror(const char *s) {
		puts(s);
	}

	void ThreeAddressCode();
	int ind=0;
	char temp='A';

	struct incod {
		Symbol opd1;
		Symbol opd2;
		char opr;
	};
%}

%token LETTER NUMBER
%left '-' '+'
%left '*' '/'

%%

program:
	statement program
	|
	;

statement: 
	lhs '=' expr ';' { AddToTable($1, $3, '='); }
	| expr ';'
	;

lhs:
   LETTER { $$ = $1; }

expr:
	expr '+' expr { $$ = AddToTable($1,$3,'+'); }
	| expr '-' expr { $$ = AddToTable($1,$3,'-'); }
	| expr '*' expr { $$ = AddToTable($1,$3,'*'); }
	| expr '/' expr { $$ = AddToTable($1,$3,'/'); }
	| '(' expr ')' { $$ = $2; }
	| NUMBER { $$ = $1; }
	| LETTER { $$ = $1; }
	;
%%

struct incod code[20]; int id=0;

Symbol AddToTable(Symbol opd1, Symbol opd2, char opr){
	Symbol res;
	code[ind].opd1=opd1;
	code[ind].opd2=opd2;
	code[ind].opr=opr;
	ind++;
	res.tag = SYM_CHAR;
	res.content.ch = temp;
	temp++;
	return res;
}

void ThreeAddressCode() {
	int cnt=0;
	temp = 'A';
	printf("\n\n\t THREE ADDRESS CODE\n\n");
	while (cnt < ind) {
		printf("%c : = \t",temp+cnt);
		// if(isalpha(code[cnt].opd1))
			print_sym(code[cnt].opd1, "\t");
		// else
		//	printf("%c\t",temp);
		printf("%c\t",code[cnt].opr);
		// if(isalpha(code[cnt].opd2))
			print_sym(code[cnt].opd2, "\t");
		// else
		//	printf("%c\t",temp);
		printf("\n");
		cnt++;
	}
}

void print_sym(Symbol s, const char *suffix) {
	switch(s.tag) {
		case SYM_NUMBER:
			printf("%d", s.content.number);
			break;
		case SYM_NAME:
			printf("%s", s.content.name);
			break;
		case SYM_CHAR:
			printf("%c", s.content.ch);
			break;
	}
	printf("%s", suffix);
}

int main(){
	printf("\nEnter the Expression: ");
	yyparse();
	temp='A';
	ThreeAddressCode();
}

