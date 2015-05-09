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
    | Start Line                         
	;
Line:
	 Declaration 
	;
Declaration:
	Global_declaration                      {  close_bss();printf("HERE"); }
	| Function START_KEYS  Scope  END_KEYS  {    }
	;
Scope:
	/* empty */							
	| Scope Local_declaration
	| Scope RETURN NUMBER SEMICOLON	
	;
Function:
	C_TYPE STRING 	START_PARENTHESES	END_PARENTHESES	
	;
Global_declaration:
	C_TYPE STRING SEMICOLON {  
                                add_symbol_to_scopes($1,$2,"__global");
                                /*print*/
                                printf("GLOBAL VARIABLE: %s - %s ",$1,$2);  
                            }
	;
Local_declaration:
	C_TYPE STRING SEMICOLON {   
                                add_symbol_to_scopes($1,$2,"__local");    
                                printf("INNER VARIABLE: %s - %s ",$1,$2);  
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
