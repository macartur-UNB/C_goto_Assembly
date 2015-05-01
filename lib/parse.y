/*
    Headers Required
*/

%{
/*      C_HEADER        */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*      INTERNAL_HEADER */
#include "global.h"

%}

%union{
	char character;
	char* string;
	int int_value;
	float float_value;
	double double_value;
}

%token <int_value> NUMBER
%token END

/*
    Pipe_line Tokens
*/
%start Start

%%

/* Expressions */
Start:
	
	| Start Line
	;
Line:
	END
	| Expression END
	;

Expression:
	NUMBER   {printf("%d", $1);}
	;

%%

/* YACC ERROR*/
void yyerror(const char *s){
	fprintf(stderr, "error: %s\n", s);
}

/* YACC MAIN*/
int main(void)
{
    extern FILE* yyin;
    yyin = fopen("Dados.txt","r");
    yyparse();
}


