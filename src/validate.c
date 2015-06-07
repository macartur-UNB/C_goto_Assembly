#include "validate.h"

/*
 *	Verify if the function was declared
 *
 * False = not found
 * True = found
 * */
int 
function_was_declared(char* function_name,
					  Function_table* functions)
{
	if(find_function(function_name,functions) != NULL)
		return 1;
	return 0;
}


/*
 *	Verify if the return of function match with function declared
 *	
 * */
int 
validate_return_of_function(char* function_name,
		Data_type return_of_function,Function_table* functions)
{
	Function* result =  find_function(function_name,functions);

	if (result == NULL) return 0;

	if (result->return_of_function == return_of_function)
		return 1;

	return 0;
}


/*
 *	Verify if global declaration was declared
 *
 * */
int 
validate_global_declaration(Symbol* symbol,Vector* scopes)
{
	return validate_symbol_declaration(symbol,"global",scopes);
}


/*
 *	Verify if local variable was declared in local and global scopes
 *	False = found
 *	True =  not found
 *
 * */
int 
validate_local_declaration(Symbol* symbol,char* scope,
						   Vector* scopes)
{
	if (!validate_symbol_declaration(symbol,"global",scopes) ||
        !validate_symbol_declaration(symbol,scope,scopes))
		return 0;
	else
		return 1;
}


/*
 * Return false if a IDENTIFIER was found in a scope 
 *
 * */
int 
validate_symbol_declaration(Symbol* symbol,char* scope,Vector* scopes)
{
	SymbolTable* current = findTable(scope,scopes); 
    while(current != NULL)
	{
		Symbol* s = current->value;
		if( s != NULL)
			if ( !strcmp(s->name,symbol->name)) 
				return 0;
        current = current->next;
	}
	return 1;
}
