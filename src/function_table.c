#include "function_table.h"
#include <stdlib.h>
#include <stdio.h>

Function_table* 
newFunctionTable(Function* value,Function_table* head,Function_table* tail,Function_table* next)
{
	Function_table* t = (Function_table*) 
						 malloc(sizeof(Function_table));
	t->head = head;
    t->value = value;
	t->tail = tail;
	t->next = next;
	return t;
}

void 
addFunctionTable(Function* function,
				 Function_table* function_table)
{
	if (function_table->head == NULL)
	{
		function_table->value = function;
		function_table->head = function_table;
		function_table->tail = function_table;
	}
	else
	{
		Function_table* next = 
				newFunctionTable(function,function_table->head,
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
	if (!current->head)
	{
		printf("FUNCTION[NONE]\n");
		return;
	}

	do
	{
		Function* f = current->value;
		current=current->next;
	}while(  current  );
}

Function* 
find_function(char* function_name,Function_table* function_table)
{
	Function_table* current = function_table;
	if (!current->head)
	{
		return NULL;
	}

	do
	{
		Function* f = current->value;
		if(!strcmp(f->name,function_name))
			return f;
		current = current->next;
	}while(current);

	return NULL;
}
