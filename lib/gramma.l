%{
#include <stdlib.h>

#include "global.h"
#include "parse.h"



/*
   
   TODO: falta tratar identifier com letra+numero+letra
         falta tratar sizeof em Expression
*/




%}

white               [ \t]+
digit               [0-9]
exponant            [eE][+-]?{integer}
line_comment        \/\/.*
multi_line_comment  \/\*([^*]|\*[^/])*\*+\/ 
pre_processor       #.*

char                \'.\' 
identifier          [a-z|A-Z|_]*
string              \".*\" 

types			    char|int|short|double|float	
ctype               {types}\**

integer             (-)?{digit}+
double              {integer}("."{integer}){exponant}?
float               {integer}("."{integer})?{exponant}?f

%%

{white}                 {   /*    SPACE IGNORED   */                }
{pre_processor}         {   /*  PRE_PROCESSOR IGNORED*/             }
{line_comment}          {   /*    LINE COMMENT IGNORED*/            }
{multi_line_comment}    {   /*    MULTILINE COMMENT IGNORED*/       }
{char}                  { yylval =  strdup(yytext); return CHAR;    }
{string}                { yylval =  strdup(yytext); return STRING;  }
{integer}               { yylval =  strdup(yytext); return INTEGER; }
{double}                { yylval =  strdup(yytext); return DOUBLE;  }
{float}                 { yylval =  strdup(yytext); return FLOAT;   }
"("                     { return   START_PARENTHESES;               }
")"                     { return   END_PARENTHESES;                 }
"{"                     { return   START_KEYS;                      }
"}"                     {  return  END_KEYS  ;                      }
"["                     {   return START_BRAKETS;                   }
"]"                     {  return  END_BRAKETS;                     }
";"                     {   return SEMICOLON;                       }
","                     {   return COMMA;                           }
"+"                     {       return PLUS;                        }
"-"                     {       return MINUS;                       }
"*"                     {       return TIMES;                       }
"/"                     {       return DIV;                         }
"%"                     {       return MOD;                         }
">"						{	return BIGGER_THAN;						}
"<"						{	return LESS_THAN;						}
">="					{	return BIGGER_OR_EQUAL;					}
"<="					{	return LESS_OR_EQUAL;					}
"=="					{	return EQUAL;							}
"!="					{   return DIFFERENT;						}
"!"						{	return NOT;								}
"="                     { return RECEIVE;                           }
{ctype}                 { yylval= strdup(yytext) ; return C_TYPE;    }
return                  {      return RETURN;                       }
{identifier}            { yylval = strdup(yytext); return IDENTIFIER;    }

%%

int yywrap() {
	close_asm();
	return 1;
}

