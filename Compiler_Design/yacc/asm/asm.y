// changes from 'official' program to support numbers & letters
// this program supports long numbers and variable names

%{
	// do this before including symbol.h
	// in every file.
	#define YYSTYPE Symbol
	#include<stdio.h>
	#include<stdlib.h>

	#include "symbol.h"

	void print_sym(Symbol sym, const char *suffix);

	Symbol AddToTable(Symbol,Symbol,char *);
	Symbol AddLoad(Symbol);
	Symbol AddStore(Symbol, Symbol);

	int yylex();
	void yyerror(const char *s) {
		puts(s);
	}

	void ThreeAddressCode();
	int ind=0;
	char temp='A';

	typedef struct instr {
		char *opr;
		Symbol opd1;
		Symbol opd2;
	} Instr;

	void printInstr(Instr);

%}

%token LETTER NUMBER
%left '-' '+' '*' '/'

%%

program:
	statement program
	|
	;

statement:
	lhs '=' expr ';' {
		AddStore($1, $3);
	}
	| expr ';'
	;

lhs:
   LETTER { $$ = $1; }

expr:
	expr '+' expr { $$ = AddToTable($1,$3,"ADD"); }
	| expr '-' expr { $$ = AddToTable($1,$3,"SUB"); }
	| expr '*' expr { $$ = AddToTable($1,$3,"MUL"); }
	| expr '/' expr { $$ = AddToTable($1,$3,"DIV"); }
	| '(' expr ')' { $$ = $2; }
	| NUMBER { $$ = $1; }
	| LETTER {
		$$ = $1;
		Symbol alloc_reg = AddLoad($1);
		char *s = $1.content.name;
		s[0] = alloc_reg.content.ch;
		s[1] = '\0';
	}
	;
%%

// instead of strcmpi, just make sure
// to use same string constant everywhere.
const char *load_opr = "LOAD";
const char *store_opr = "STORE";

Instr code[20]; int id=0;

Symbol AddToTable(Symbol opd1, Symbol opd2, char *opr){
	if (opr == store_opr) {
		temp--;
	}
	Symbol res;
	code[ind].opr=opr;
	code[ind].opd1=opd1;
	code[ind].opd2=opd2;
	// print instructions as they are added
	// no need to call ThreeAddressCode separately.
	// This allows us to overwrite contents of symbol.name
	// and save it as a register name.
	// (Register names are A-Z)
	printf("%s\t", opr);
	if (opr != store_opr)
		printf("%c\t", temp);
	print_sym(opd1, "\t");
	if (opr != load_opr)
		print_sym(opd2, "");
	printf("\n");
	ind++;
	res.tag = SYM_CHAR;
	res.content.ch = temp;
	temp++;
	return res;
}

Symbol AddStore(Symbol opd, Symbol val) {
	return AddToTable(opd, val, (char *)store_opr);
}

Symbol AddLoad(Symbol opd) {
	Symbol extra = { .tag = SYM_CHAR, .content = { .ch = '?' }};
	return AddToTable(opd, extra, (char *)load_opr);
}

void printInstr(Instr i) {
	printf("%s\t", i.opr);
	print_sym(i.opd2, "\n");
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
}

