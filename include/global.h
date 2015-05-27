#include "util.h"

#define YYSTYPE char*

/* PREVIOUS DECLARATION */
extern yylineno;
extern YYSTYPE yylval;
extern FILE* yyin;

int yylex();
void yyerror(const char *s);

/* INTERNAL EXTERN*/
extern char* extract_data_type( char* data_type);
