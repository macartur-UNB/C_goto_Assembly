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
    | Start Line                        {printf("1");} 
	;
Line:
	 Declaration						     {printf("2");} 
 
	;
Declaration:
	Global_declaration                        {printf("3");close_bss();} 
	| Function START_KEYS  Scope  END_KEYS   {printf("4");} 
	;
Scope:
	/* empty */							
	| Scope Local_declaration 				{printf("5");} 
	| Scope RETURN LITERAL SEMICOLON   {printf("6");}	
	| Scope Expression
	;
Function:
	C_TYPE IDENTIFIER	START_PARENTHESES	END_PARENTHESES	 {printf("7");}
	;
Global_declaration:
	C_TYPE IDENTIFIER SEMICOLON {add_symbol_to_scopes($1,$2,"1",1,"__global");printf("8");}
	;
Local_declaration:
	C_TYPE IDENTIFIER SEMICOLON {add_symbol_to_scopes($1,$2,"1",1,"__local");    printf("9 - %s",$1);}
	;

Expression:
    LITERAL { $$ =$1; /* printf("LITERAL %s",$1);*/}
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
