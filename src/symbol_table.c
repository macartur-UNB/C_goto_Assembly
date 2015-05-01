#include <stdlib.h>
#include "symbol_table.h"

#include <stdio.h>


void 
freeSymbolTable(SymbolTable * symbol_table)
{
	printf("liberando a symbol table: %s\n",symbol_table->scope);
	SymbolTable* table = symbol_table;
	while( table )
	{
		freeSymbol(table->value);
		SymbolTable* next = table->next;
		free(table);
		table = next;
	}
	table = NULL;
	symbol_table	= NULL;
}

SymbolTable* 
newSymbolTable( char* scope )
{
	return createSymbolTable(scope,NULL,NULL,NULL,NULL);
}


SymbolTable* 
createSymbolTable(char* scope, SymbolTable* head, SymbolTable* tail,
									 Symbol* value,SymbolTable* next  )
{
	SymbolTable* result = (SymbolTable*) malloc(sizeof(SymbolTable)); 
	if(! scope ){
		result->scope = NULL;
	}
	else
	{
		result->scope =  scope;
	}
	
	if (! head )
	{
		result->head = NULL;
	}
	else
	{
		result->head =  head;
	}
	
	if (! tail )
	{
		result->tail = NULL;
	}
	else
	{
		result->tail =  tail;
	}
	
	if (!value){
		result->value = NULL;
	}
	else
	{
		result->value =  value;
	}
	
	if (!next)
	{
		result->next = NULL;
	}
	else
	{
		result->next =  next;
	}	

	return result; 
}


void printTable(SymbolTable* table){
	printf("**scope= %s  \n*** name = %s \n*** head = %p\n*** tail = %p \n*** next = %p",
				table->scope,table->value->name,table->head,table->tail,table->next
			);

}


void 
addSymbol(Symbol * symbol,SymbolTable* symbol_table)
{

	if ( ! symbol_table->head )
	{
		printf("TABLE EMPTY\n");
		printf("**added %s**\n",symbol->name);
		symbol_table->head = symbol_table;
		symbol_table->tail = symbol_table;
		symbol_table->value = symbol;
		printTable(symbol_table);
		return;
	}

	SymbolTable* last = symbol_table->tail;
	SymbolTable* first = symbol_table->head;

	SymbolTable* next = createSymbolTable(symbol_table->scope,
										  first,
                                          last,
                                          symbol,
										  NULL);

	
	last->next = next;
	symbol_table->tail = next;

	printf("\nnext = \n");
	printTable(next);
}

Symbol*
findSymbol(char* name,SymbolTable* symbol_table){
	
	SymbolTable* ptr = symbol_table;
	while( ptr)
	{
		printf("--%s--\n",ptr->value->name);
		if(ptr->value->name == name)
			return ptr->value;
		ptr = ptr->next;
	}
	return NULL;

}

Symbol* 
findChar	(char* name, char char_value,SymbolTable* symbol_table)
{
	SymbolTable* next = symbol_table->next;	

	while(next)	
	{
		Symbol* symbol = symbol_table->value;

		if( name && symbol->name == name || 
			char_value && symbol->char_value == char_value)
			return symbol;
		next = next->next;
	}
	return NULL;

}

Symbol* 
findShort	(char* name, short short_value,SymbolTable* symbol_table)
{
	SymbolTable* next = symbol_table->next;	

	while(next)	
	{
		Symbol* symbol = symbol_table->value;

		if( name && symbol->name == name || 
			short_value && symbol->short_value == short_value)
			return symbol;
		next = next->next;
	}
	return  NULL;

}

Symbol* 
findInt		(char* name, int int_value,SymbolTable* symbol_table)
{
	SymbolTable* next = symbol_table->next;	

	while(next)	
	{
		Symbol* symbol = symbol_table->value;

		if( name && symbol->name == name || 
			int_value && symbol->int_value == int_value)
			return symbol;
		next = next->next;
	}
	return NULL;

}

Symbol* 
findLong	(char* name, long long_value,SymbolTable* symbol_table)
{
	SymbolTable* next = symbol_table->next;	

	while(next)	
	{
		Symbol* symbol = symbol_table->value;

		if( name && symbol->name == name || 
			long_value && symbol->long_value == long_value)
			return symbol;
		next = next->next;
	}
	return NULL;

}

Symbol* 
findFloat	(char* name, float float_value,SymbolTable* symbol_table)
{
	SymbolTable* next = symbol_table->next;	

	while(next)	
	{
		Symbol* symbol = symbol_table->value;

		if( name && symbol->name == name || 
			float_value && symbol->float_value == float_value)
			return symbol;
		next = next->next;
	}
	return NULL;

}

Symbol* 
findDouble	(char* name, double double_value,SymbolTable* symbol_table)
{
	SymbolTable* next = symbol_table->next;	

	while(next)	
	{
		Symbol* symbol = symbol_table->value;

		if( name && symbol->name == name || 
			double_value && symbol->double_value == double_value)
			return symbol;
		next = next->next;
	}
	return NULL;

}

Symbol* 
findPoiter	(char* name, unsigned int ptr_level, Data_type ptr_type,
					 void* ptr_value,SymbolTable* symbol_table)
{
	SymbolTable* next = symbol_table->next;	

	while(next)	
	{
		Symbol* symbol = symbol_table->value;

		if( name && symbol->name == name || 
			ptr_value && symbol->ptr_value == ptr_value &&
			ptr_type && symbol->ptr_type == ptr_type &&
			ptr_level && symbol->ptr_level == ptr_level	)
			return symbol;
		next = next->next;
	}
	return NULL;

}

