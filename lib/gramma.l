%{
#include <stdlib.h>

#include "global.h"
#include "parse.h"
%}

white               [ \t]+
digit               [0-9]
integer             {digit}+
exponant            [eE][+-]?{integer}
number              {integer}("."{integer})?{exponant}?
line_comment        \/\/.*
multi_line_comment  \/\*([^*]|\*[^/])*\*+\/ 
identifier              [a-z|A-Z|_]*
pre_processor       #.*
string				{identifier}

%%

{white}                 {   /*    SPACE IGNORED   */                }
{pre_processor}         {   /*  PRE_PROCESSOR IGNORED*/             }
{line_comment}          {   /*    LINE COMMENT IGNORED*/            }
{multi_line_comment}    {   /*    MULTILINE COMMENT IGNORED*/       }
{number}                { yylval.string =  yytext ; return NUMBER;  }

"("                     { return   START_PARENTHESES;               }
")"                     { return   END_PARENTHESES;                 }
"{"                     { return   START_KEYS;                      }
"}"                     {  return  END_KEYS  ;                      }
"["                     {   return START_BRAKETS;                   }
"]"                     {  return  END_BRAKETS;                     }
";"                     {   return SEMICOLON;                       }
","                     {   return COMMA;                           }

">"						{	return BIGGER_THAN;						}
"<"						{	return LESS_THAN;						}
">="					{	return BIGGER_OR_EQUAL;					}
"<="					{	return LESS_OR_EQUAL;					}
"=="					{	return EQUAL;							}
"!="					{   return DIFFERENT;						}
"!"						{	return NOT;								}

int                     { yylval.string= yytext ; return C_TYPE;    }
char                    { yylval.string= yytext ; return C_TYPE;    }
short                   { yylval.string= yytext ; return C_TYPE;    }
double                  { yylval.string= yytext ; return C_TYPE;    }
float                   { yylval.string= yytext ; return C_TYPE;    }
return                  {      return RETURN;                       }
{string}                { yylval.string = yytext ; return STRING;   }

%%

int yywrap() {
	return 0;
}

