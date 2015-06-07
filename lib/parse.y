
%{
#include <stdio.h>
#include <stdlib.h>

#include "global.h"

#include <string.h>

%}

%token IDENTIFIER
%token CHAR
%token STRING 
%token INTEGER
%token FLOAT
%token DOUBLE
    
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
	Global_declaration  							{	close_bss(); close_data(); } 
    | Function START_KEYS  Scope  END_KEYS			{	end_function(); 	}
	;
Scope:
	/* empty */							
	| Scope Local_declaration 			 
	| Scope RETURN Literal SEMICOLON   
	| Scope Expression SEMICOLON;
	;
Function:
	C_TYPE IDENTIFIER	START_PARENTHESES	END_PARENTHESES	 
        {  
            initialize_functions($2,$1);
            printf("Function: %s\n", $2);
        }
	;
Global_declaration:
    /* Global Uninitialized Variable */
	C_TYPE IDENTIFIER SEMICOLON
        {
            add_symbol_to_scopes($1,$2,"0",0);
            printf("Global Uninitialized Variable %s\n", $2);
        }
    
    /* Global Initialized Variable */
    | C_TYPE IDENTIFIER RECEIVE Literal SEMICOLON
        {
            add_symbol_to_scopes($1,$2,$4,1);
            printf("Global Initialized Variable %s = %s\n", $2, $4);
        }
	;
Local_declaration:
	/* Local Uninitialized Variable */
    C_TYPE IDENTIFIER SEMICOLON 
        {    
            add_symbol_to_scopes($1,$2,"0",0);
            printf("\tLocal Variable %s\n",$2);
        }
    
    /* Local Initialized Variable */
    | C_TYPE IDENTIFIER RECEIVE Literal SEMICOLON
        {   
            add_symbol_to_scopes($1,$2,$4,1);
            printf("\tLocal Initialized Variable %s = %s\n", $2, $4);
        }
	;

Literal:
    INTEGER { $$=$1;}
    | FLOAT { $$=$1;}
    | DOUBLE { $$=$1;}
    | CHAR { $$=$1;}
    | STRING { $$=$1;}
    ;

Expression:
	IDENTIFIER {$$=$1; push_to_operand_stack(get_variable_data_type(strdup($$)), 0, strdup($$)); }
    | INTEGER  {$$ = $1; push_to_operand_stack(INT_T, 1, strdup($$));}
    | FLOAT  {$$ = $1; push_to_operand_stack(FLOAT_T, 1, strdup($$));}
    | DOUBLE {$$ = $1; push_to_operand_stack(DOUBLE_T, 1, strdup($$));}
    | CHAR   {$$ = $1; push_to_operand_stack(CHAR_T, 1, strdup($$));}
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
	fprintf(stderr, "Error: line %d - %s\n",yylineno, s);
}


/* YACC MAIN*/
int main(void)
{
    char file_name[50] = "main";
    char file_in[50];
    sprintf(file_in,"%s.c",file_name);
    init_asm(file_name);
    yyin = fopen(file_in,"r");
    yylineno = 1; // count of files
    yyparse();
}
