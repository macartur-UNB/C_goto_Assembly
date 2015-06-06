#include "symbol.h"

Symbol* 
createSymbol()
{
	return (Symbol*) malloc(sizeof(Symbol));
}

Symbol* 
newChar(char* name, char char_value, int initialized)
{
	Symbol* result = createSymbol(); 
	
    result->data_type 		= CHAR_T;
	result->initialized     = initialized;
	result->name 			= name;
	result->char_value 		= char_value;

	return result;
}

Symbol* 
newShort(char* name, short short_value, int initialized)
{
	Symbol* result = createSymbol();

    result->data_type		= SHORT_T;
	result->name 			= name;
	result->initialized     = initialized;
	result->short_value 	= short_value;

	return result;
}

Symbol* 
newInt( char* name, int int_value, int initialized)
{
	Symbol* result  = createSymbol();

	result->data_type 		= INT_T;
	result->name 			= name;
	result->initialized     = initialized;
	result->int_value 		= int_value;

	return result;
}

Symbol* 
newLong(char* name, long long_value, int initialized)
{
	Symbol* result  = createSymbol();

	result->data_type 		= LONG_T;
	result->name 			= name;
	result->initialized     = initialized;
	result->long_value 		= long_value;

	return result;
}

Symbol* 
newFloat(char* name,float float_value, int initialized)
{
	Symbol* result  = createSymbol();

	result->data_type 		= FLOAT_T;
	result->name 			= name;
	result->initialized     = initialized;
	result->float_value 	= float_value;

	return result;
}

Symbol* 
newDouble(char* name, double double_value, int initialized)
{
	Symbol* result  = createSymbol();

	result->data_type 		= DOUBLE_T;
	result->name 			= name;
	result->initialized     = initialized;
	result->double_value 	= double_value;

	return result;
}

Symbol* 
newPoiter(char* name, unsigned int ptr_level, 
				  Data_type ptr_type, void* ptr_value, int initialized)
{
	Symbol* result  = createSymbol();

	result->data_type 		= PTR_T;
	result->name 			= name;
	result->initialized     = initialized;
	result->ptr_level 		= ptr_level;
	result->ptr_type		= ptr_type;
	result->ptr_value		= ptr_value;

	return result;
}

void 
freeSymbol(Symbol* symbol)
{
	free(symbol);
	symbol = NULL;	
}

/*
 *	Return a size used to stack 
 * */
size_t symbol_size(Symbol* symbol)
{
	
	switch(symbol->data_type)
	{
		case CHAR_T:
		case SHORT_T:
		case INT_T:
		case FLOAT_T:
			return 2;

		case LONG_T:
		case DOUBLE_T:
		case PTR_T:
			return 4;
		break;
	}
	return 0;
}



