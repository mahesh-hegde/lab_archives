%{
	#include<stdlib.h>

%}

%%
[abc]	return yytext[0];
[ \n\t] ;
.       printf("Unexpected: %s\n", yytext);
%%

