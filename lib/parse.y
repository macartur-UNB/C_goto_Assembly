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
    int int_value;
	char character;
	char* string;
}


/* variables */
%token <string> NUMBER
%token <string> STRING


/*
	C TYPE
*/
%token <string> C_TYPE

/*
     OTHERS	
*/
%token RETURN
%token SEPARATOR COMMA
%token END
%token START_PARENTHESES END_PARENTHESES
%token START_KEYS END_KEYS
%token START_BRAKETS END_BRAKETS

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
	 Declaration 
	;
Declaration:
	Variable 
	| Function START_KEYS  Scope  END_KEYS
	;
Scope:
	/* empty */							{ printf("scope");  }
	| Scope Variable
	| Scope RETURN NUMBER SEPARATOR		{ printf("RETURN");  } 
	;
Function:
	C_TYPE STRING 	START_PARENTHESES	END_PARENTHESES	{ printf("FUNCTION");   }	
	;
Variable:
	C_TYPE STRING SEPARATOR				{ printf("VARIABLES");	}
	;


%%

/* YACC ERROR*/
void yyerror(const char *s){
	fprintf(stderr, "error: %s\n", s);
}

/* YACC MAIN*/
int main(void)
{

	Vector* vector = newVector(); 	

    extern FILE* yyin;
    yyin = fopen("Dados.txt","r");
    yyparse();
}


