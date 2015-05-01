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

white [ \t]+
digit [0-9]
integer {digit}+
exponant [eE][+-]?{integer}
number {integer}("."{integer})?{exponant}?
line_comment \/\/.*
multi_line_comment \/\*([^*]|\*[^/])*\*+\/ 

%%

{white}             {  /*    SPACE IGNORED   */ }
{line_comment}      { /*   */   }
{multi_line_comment}      { /*   */   }
{integer}            { yylval.int_value =  atoi(yytext) ; return NUMBER;            }


%%

int yywrap() {
	return 0;
}

