%{
	#include <stdio.h>
	#include <assert.h>
	#include "calc.h"
	#include "calc_tab.h"

	static int pop();
	static int top();
	static void push(int val);
%}

%token T_INT

%%

S	: S E '\n' { printf("= %d\n", top()); }
  	|
	;

E	: E E '+' { push(pop() + pop()); }
  	| E E '-' { int op2 = pop(); push(pop() - op2); }
	| E E '*' { push(pop() * pop()); }
	| E E '/' { int op2 = pop(); push(pop() / op2); }
	| T_INT   { push(yylval); }
	;

%%

static int stack[100], count = 0;

static int pop()
{
	assert(count > 0);
	return stack[--count];
}

static int top()
{
	assert(count > 0);
	return stack[count - 1];
}

static void push(int val)
{
	assert(count < sizeof(stack) / sizeof(*stack));
	stack[count++] = val;
}

void yyerror(const char *msg)
{
	fprintf(stderr, "ERROR: %s\n", msg);
}

int main()
{
	return yyparse();
}
