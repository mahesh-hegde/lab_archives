spacing [ \t]*
digits [0-9]+

decimal {digits}"."{digits}
neg_int "-"{digits}
pos_int "+"?{digits}
neg_dec "-"{decimal}
pos_dec "+"?{decimal}
div {spacing}"/"{spacing}

neg_frac {neg_int}{div}{pos_int}|{pos_int}{div}{neg_int}
pos_frac {pos_int}{div}{pos_int}|{neg_int}{div}{neg_int}

%{
	#include<string.h>
	int pi = 0, pd = 0, ni = 0, nd = 0;
%}

%%
{neg_dec}|{neg_frac}    nd++;
{pos_dec}|{pos_frac}    pd++;
{neg_int}               ni++;
{pos_int}               pi++;
[ ,\n\t]                 ;  // suppress default action, not even printing
%%

int main() {
	yylex();
	printf("Positive integers: %d\n", pi);
	printf("Negative integers: %d\n", ni);
	printf("Positive fractions: %d\n", pd);
	printf("Negative fractions: %d\n", nd);
}

