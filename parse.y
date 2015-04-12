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

/* PREVIOUS DECLARATION */
int yylex();
void yyerror(const char *s);
%}

/*
    Token Definition
*/

/*
   Arithimetic Tokens
*/
%token NUMBER
%token PLUS MINUS TIMES DIVIDE REST
%token NEG
/*  Priority   */
%left PLUS MINUS
%left DIVIDE TIMES
%right NEG



/*
    Type Tokens
*/
%token BOOL INT VOID FLOAT DOUBLE CHAR
%token FILE_TOKEN 

/*
    Logical Tokens
*/
%token AND OR XOR NOT 
%token AND_AND OR_OR
%token ASSIGNMENT
%token INCREMENT DECREMENT 
%token DIVIDE_EQUAL TIMES_EQUAL REST_EQUAL
%token FALSE TRUE NULL_TOKEN
%token COMPARE_EQUAL COMPARE_MORE COMPARE_LESS
%token COMPARE_MORE_EQUAL COMPARE_LESS_EQUAL

/*
    Conditional Tokens
*/
%token IF ELSE WHILE FOR DO 
%token LEFT_BRACKETS RIGHT_BRACKETS
%token LEFT_PARENTHESIS RIGHT_PARENTHESIS
%token LEFT_KEYS RIGHT_KEYS

/*
    Comment Tokens
*/
%token BEGIN_MULTILINE_COMMENT END_MULTILINE_COMMENT
%token LINE_COMMENT

/*
    Headers Tokens
*/
%token HEADER_TOKEN IF_NDEF DEFINE INCLUDE END_IF

/*
    Function Tokens
*/
%token MAIN
%token RETURN

/*
    Others Tokens
*/
%token END


/*
    Pipe_line Tokens
*/
%start Start


%%

Start:
    /* EMPTY */
    | Start Line
    ;
Line:
    END
    | Expression END                                    { printf("Result: %f\n",$1); }
    ;
Expression:
    NUMBER                                              { $$ = $1;      }
    | Expression PLUS Expression                        { $$ = $1 + $3; }
    | Expression MINUS Expression                       { $$ = $1 - $3; }
    | Expression TIMES Expression                       { $$ = $1 * $3; }
    | Expression DIVIDE Expression                      { $$ = $1 / $3; }
    | MINUS Expression %prec NEG                        { $$ = -$1;     }
    | LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS     { $$ = $2;      }
    ;
%%
/* YACC ERROR*/
void yyerror(const char *s){
}

/* YACC MAIN*/
int main(void)
{
    yyparse();
}


