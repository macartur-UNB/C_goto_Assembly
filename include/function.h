#ifndef FUNCTION_H
#define FUNCTION_H

#include "symbol.h"

typedef struct _Function
{
	char* name;
	Data_type return_of_function;
}Function;

Function* new_function(Data_type return_of_function, char* name);
void free_function(Function* function);

#endif
