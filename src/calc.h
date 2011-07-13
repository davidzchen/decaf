#ifndef _CALC_H
#define _CALC_H

#include <stdio.h>

extern char *yytext;

int yylex();

void yyerror(const char *msg);

#endif
