#include "util.h"

/* PREVIOUS DECLARATION */

int yylex();
void yyerror(const char *s);
extern FILE* yyin;

/* INTERNAL EXTERN*/
extern char* extract_data_type( char* data_type);
