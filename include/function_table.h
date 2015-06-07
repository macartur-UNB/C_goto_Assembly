#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H
#include "function.h"

typedef struct _Function_table {
    Function* value;
	struct _Function_table* tail;
	struct _Function_table* next;
}Function_table;

Function_table* newFunctionTable(Function* value,Function_table* tailf,Function_table* next);
void addFunctionTable(Function* function,Function_table* function_table);
Function* find_function(char* function_name,Function_table* function_table);
void free_function_table(Function_table* function_table);
void print_functions(Function_table* function_table);

#endif
