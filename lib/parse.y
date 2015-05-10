/*
    Headers Required
*/

%{
/*      C_HEADER        */
#include <stdio.h>
#include <stdlib.h>

/*      INTERNAL_HEADER */
#include "global.h"
#include <string.h>
%}

%union{
    int int_value;
    char character;
    char* string;
}


%token <string> NUMBER
%token <string> STRING


%token <string> C_TYPE


/*
    COMPARE
*/
%token BIGGER_THAN LESS_THAN 
%token BIGGER_OR_EQUAL LESS_OR_EQUAL
%token EQUAL DIFFERENT NOT

%token RETURN
%token SEMICOLON COMMA
%token START_PARENTHESES END_PARENTHESES
%token START_KEYS END_KEYS
%token START_BRAKETS END_BRAKETS

/*
    Pipe_line Tokens
*/
%start Start

%%

Start:
    | Start Line                        {printf("1");} 
	;
Line:
	 Declaration						     {printf("2");} 
 
	;
Declaration:
	Global_declaration                        {printf("3");} 
	| Function START_KEYS  Scope  END_KEYS   {printf("4");} 
	;
Scope:
	/* empty */							
	| Scope Local_declaration 				{printf("5");} 
	| Scope RETURN NUMBER SEMICOLON   {printf("6");}	
	;
Function:
	C_TYPE STRING 	START_PARENTHESES	END_PARENTHESES	 {printf("7");}
	;
Global_declaration:
	C_TYPE STRING SEMICOLON {   
                                add_symbol_to_scopes($1,$2,"1","__global");{printf("8");}
                            }
	;
Local_declaration:
	C_TYPE STRING SEMICOLON {   
                                add_symbol_to_scopes($1,$2,"1","__local");    {printf("9");}
                                }
	;
    

%%

/* YACC ERROR*/
void yyerror(const char *s){
	fprintf(stderr, "error: %s\n", s);
}

/* YACC MAIN*/
int main(void)
{
    init_asm();
    yyin = fopen("main.c","r");
    yyparse();
}
