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
real {integer}("."{integer})?{exponant}?

%%

{white} {	/*   WE IGNORE WHITE CHARACTERS */	}
{real}	{
			yylval = atof(yytext);
			return (NUMBER);
		}	

"+"						return (PLUS);
"-"						return (MINUS);
"*"						return (TIMES);
"/"						return (DIVIDE);
"%"						return (REST);
"bool"					return (BOOL);
"int"					return (INT);
"void"					return (VOID);
"float"					return (FLOAT);
"double"				return (DOUBLE);
"char"					return (CHAR);
"FILE"					return (FILE_TOKEN);
"&"						return (AND);
"|"						return (OR);
"^"						return (XOR);
"!"						return (NOT);
"&&"					return (AND_AND);
"||"					return (OR_OR);
"="						return (ASSIGNMENT);
"++"					return (INCREMENT);
"--"					return (DECREMENT);
"/="					return (DIVIDE_EQUAL);
"*="					return (TIMES_EQUAL);
"%="					return (REST_EQUAL);
"NULL"					return (NULL_TOKEN);
"false"					return (FALSE);
"true"					return (TRUE);
"=="					return (COMPARE_EQUAL);
">"						return (COMPARE_MORE);
"<"						return (COMPARE_LESS);
">="					return (COMPARE_MORE_EQUAL);
"<="					return (COMPARE_LESS_EQUAL);
"if"					return (IF);
"else"					return (ELSE);
"while"					return (WHILE);
"for"					return (FOR);
"do"					return (DO);
"["						return (LEFT_BRACKETS);
"]"						return (RIGHT_BRACKETS);
"("						return (LEFT_PARENTHESIS);
")"						return (RIGHT_PARENTHESIS);
"{"						return (LEFT_KEYS);
"}"						return (RIGHT_KEYS);
"/*"					return (BEGIN_MULTILINE_COMMENT);
"*/"					return (END_MULTILINE_COMMENT);
"//"					return (LINE_COMMENT);
"#"						return (HEADER_TOKEN);
"ifndef"				return (IF_NDEF);
"define"				return (DEFINE);
"endif"					return (END_IF);
"main"					return (MAIN);
"return"				return (RETURN);
"\n"					return (END);
[a-zA-Z0-9]+			return (ANYTHING_ELSE);
";"						return (END_INSTRUCTION);
[a-zA-Z_]+				return (VARIABLE_NAME);

%%

int yywrap() {
	return 0;
}

