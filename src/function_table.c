#include "function_table.h"
#include <stdlib.h>
#include <stdio.h>

Function_table* 
newFunction_table()
{
	Function_table* t = (Function_table*) 
						 malloc(sizeof(Function_table));
    t->value = NULL;
	t->tail = NULL;
	t->next = NULL;
}

Function_table* 
addFunction(Function* function,Function_table* function_table)
{
	if (function_table->value == NULL)
	{
		function_table->value = function;
		function_table->tail = function_table;
	}
	Function_table* next = newFunction_table();
	next->value = function;
	function_table->tail->next=next;
	function_table->tail = next;

	return function_table;
}

void 
free_function_table(Function_table* function_table)
{
	Function_table* current = function_table;
	while(current->next != NULL)
	{
	    free_function(current->value); 	
		free(current);
		current = current->next;
	}
}

void 
print_functions(Function_table* function_table)
{
	Function_table* current = function_table;
	while( current->next != NULL)
	{
		Function* f = current->value;
		printf("Function(%s)", f->name);
		current = current->next;
	}
}

Function* 
find_function(char* function_name,Function_table* function_table)
{
	Function_table* current = function_table;
	while( current->next != NULL)
	{
		Function* f = current->value;
		if (!strcmp(f->name, function_name))
				return f;
		current = current->next;
	}
	return NULL;
}
