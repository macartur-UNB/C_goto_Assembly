%{
#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include <string.h>
%}

%token  IDENTIFIER
%token  LITERAL

%token  C_TYPE

%token PLUS
%token MINUS
%token TIMES
%token DIV
%token MOD

%left PLUS MINUS
%left TIMES DIV
%right MOD


%token RECEIVE
%token BIGGER_THAN LESS_THAN 
%token BIGGER_OR_EQUAL LESS_OR_EQUAL
%token EQUAL DIFFERENT NOT

%token RETURN
%token END
%token SEMICOLON COMMA
%token START_PARENTHESES END_PARENTHESES
%token START_KEYS END_KEYS
%token START_BRAKETS END_BRAKETS

%start Start

%%

Start:
    | Start Line                     
	;
Line:
	 Declaration					 
	;
Declaration:
	Global_declaration                        
        {
            close_bss(); 
            close_data();
        } 
    | Function START_KEYS  Scope  END_KEYS
	;
Scope:
	/* empty */							
	| Scope Local_declaration 			 
	| Scope RETURN LITERAL SEMICOLON   
	| Scope Expression SEMICOLON;
	;
Function:
	C_TYPE IDENTIFIER	START_PARENTHESES	END_PARENTHESES	 
        {
            printf("Function: %s", $2);
        }
	;
Global_declaration:
    /* Global Uninitialized Variable */
	C_TYPE IDENTIFIER SEMICOLON
        {
            add_symbol_to_scopes($1,$2,"0",0,"__global");
            printf("Global Uninitialized Variable %s", $2);
        }
    
    /* Global Initialized Variable */
    | C_TYPE IDENTIFIER RECEIVE LITERAL SEMICOLON
        {
            add_symbol_to_scopes($1,$2,$4,1,"__global");
            printf("Global Initialized Variable %s = %s", $2, $4);
        }
	;
Local_declaration:
	/* Local Uninitialized Variable */
    C_TYPE IDENTIFIER SEMICOLON 
        {    
            printf("\tLocal Variable %s",$2);
        }
    
    /* Local Initialized Variable */
    | C_TYPE IDENTIFIER RECEIVE LITERAL SEMICOLON
        {   
            printf("\tLocal Initialized Variable %s = %s", $2, $4);
        }
	;

Expression:
    LITERAL 
        {
            $$ = $1;
            /* push_to_operand_stack($$); */
        }
	| START_PARENTHESES Expression END_PARENTHESES { $$ = $2 ;printf("( %s )",$2);   }
	| Expression PLUS Expression     {  
										char string_v[100];
										sprintf(string_v,"%s+%s",$1,$3);
										$$ = string_v;
										printf("%s + %s\n",$1,$3); 
									  }
	| Expression MINUS Expression     { 
										char string_v[100];
										sprintf(string_v,"%s-%s",$1,$3);
										$$ = string_v;
										 printf("%s - %s\n",$1,$3); 
									  }
	| Expression TIMES Expression     {
										char string_v[100];
										sprintf(string_v,"%s*%s",$1,$3);
										$$ = string_v;
										printf("%s * %s\n",$1,$3); 
										}
	| Expression DIV Expression        {
										char string_v[100];
										sprintf(string_v,"%s/%s",$1,$3);
										$$ = string_v;
										printf("%s / %s\n",$1,$3); 
										}

	| Expression MOD Expression    {
										char string_v[100];
										sprintf(string_v,"%s mod %s",$1,$3);
										$$ = string_v;
										printf("%s mod %s\n",$1,$3); 
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
