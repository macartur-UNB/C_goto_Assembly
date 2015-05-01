#include "symbol.h"


Symbol* 
createSymbol()
{
	return (Symbol*) malloc(sizeof(Symbol));
}

Symbol* 
newChar(char* name, char char_value)
{
	Symbol* result = createSymbol(); 
	
    result->data_type 		= CHAR_T;
	result->name 			= name;
	result->char_value 		= char_value;

	return result;
}

Symbol* 
newShort(char* name, short short_value)
{
	Symbol* result = createSymbol();

    result->data_type		= SHORT_T;
	result->name 			= name;
	result->short_value 	= short_value;

	return result;
}

Symbol* 
newInt( char* name, int int_value)
{
	Symbol* result  = createSymbol();

	result->data_type 		= INT_T;
	result->name 			= name;
	result->int_value 		= int_value;

	return result;
}

Symbol* 
newLong(char* name, long long_value)
{
	Symbol* result  = createSymbol();

	result->data_type 		= LONG_T;
	result->name 			= name;
	result->long_value 		= long_value;

	return result;
}

Symbol* 
newFloat(char* name,float float_value)
{
	Symbol* result  = createSymbol();

	result->data_type 		= FLOAT_T;
	result->name 			= name;
	result->float_value 	= float_value;

	return result;
}

Symbol* 
newDouble(char* name, double double_value)
{
	Symbol* result  = createSymbol();

	result->data_type 		= DOUBLE_T;
	result->name 			= name;
	result->double_value 	= double_value;

	return result;
}

Symbol* 
newPoiter(char* name, unsigned int ptr_level, 
				  Data_type ptr_type, void* ptr_value)
{
	Symbol* result  = createSymbol();

	result->data_type 		= PTR_T;
	result->name 			= name;
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

