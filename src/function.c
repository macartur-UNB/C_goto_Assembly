#include "function.h"


Function* 
new_function(Data_type return_of_function, char* name)
{
	Function* result;
	result = (Function*) malloc(sizeof(Function));	
	result->return_of_function = return_of_function;
    result->name = name;	
}

void 
free_function(Function* function)
{
	free(function);
}
