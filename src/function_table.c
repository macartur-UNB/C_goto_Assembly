#include "function_table.h"
#include <stdlib.h>
#include <stdio.h>

Function_table* 
newFunctionTable(Function* value,Function_table* tail,Function_table* next)
{
	Function_table* t = (Function_table*) 
						 malloc(sizeof(Function_table));
    t->value = value;
	t->tail = tail;
	t->next = next;
	return t;
}

void 
addFunctionTable(Function* function,
				 Function_table* function_table)
{
	Function* f = function_table->value;

	if (f == NULL)
	{
		function_table->value = function;
		function_table->tail = function_table;
	}
	else
	{
		Function_table* next = newFunctionTable(function,
								     function_table->tail,NULL);
		function_table->tail->next=next;
		function_table->tail = next;
	}
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
		printf("Function[%s]\n", f->name);
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
