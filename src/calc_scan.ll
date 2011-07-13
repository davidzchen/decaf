%{
	#include "calc.h"
	#include "calc_tab.h"
%}
%%

[0-9]+		{ yylval = atoi(yytext); return T_INT; }
[-+*/\n]	{ return yytext[0]; }
.		{}

%%
