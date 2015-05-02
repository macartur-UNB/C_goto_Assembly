/*
	Headers Required
*/

%{
/*	C_HEADER */
#include <stdlib.h>

/*	INTERNAL_HEADER  */
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
string              [a-z|A-Z|_|*]*
pre_processor       #.*

%%

{white}                 {   /*    SPACE IGNORED   */                }
{pre_processor}         {   /*  PRE_PROCESSOR IGNORED*/             }
{line_comment}          {   /*    LINE COMMENT IGNORED*/            }
{multi_line_comment}    {   /*    MULTILINE COMMENT IGNORED*/       }
{number}                { yylval.string =  yytext ; return NUMBER;  }

"("                      { return START_PARENTHESES;                 }
")"                       { return END_PARENTHESES;                   }
"{"                       { return START_KEYS;                        }
"}"                     {  return END_KEYS  ;                          }
"["                    {   return START_BRAKETS;                      }
"]"                     {  return END_BRAKETS;                      }
";"                     {   return  SEPARATOR;                      }
","                     {   return COMMA;                        }
int                  { yylval.string= yytext ; return C_TYPE;    }
char                  { yylval.string= yytext ; return C_TYPE;    }
short                  { yylval.string= yytext ; return C_TYPE;    }
double                  { yylval.string= yytext ; return C_TYPE;    }
float                  { yylval.string= yytext ; return C_TYPE;    }
return                  {      return RETURN;                       }
{string}                { yylval.string = yytext ; return STRING;   }




%%

int yywrap() {
	return 0;
}

