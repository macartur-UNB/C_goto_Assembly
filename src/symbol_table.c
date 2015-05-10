#include <stdlib.h>
#include "symbol_table.h"

void 
freeSymbolTable(SymbolTable * symbol_table)
{
	SymbolTable* table = symbol_table;
	while( table != NULL )
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




void 
addSymbol(Symbol * symbol,SymbolTable* symbol_table)
{

	if ( symbol_table->head == NULL )
	{
		symbol_table->head = symbol_table;
		symbol_table->tail = symbol_table;
		symbol_table->value = symbol;
		return;
	}

	SymbolTable* next = createSymbolTable(symbol_table->scope,
										  symbol_table->head,
                                          symbol_table->tail,
                                          symbol,
										  NULL);

	symbol_table->tail->next = next;
	symbol_table->tail = next;
}

Symbol*
findSymbol(char* name,SymbolTable* symbol_table){
		
	if (symbol_table == NULL &&  symbol_table->head !=NULL || name == NULL)
		return NULL;

	SymbolTable* next = symbol_table;

	while(next)
	{
		if( next->value->name == name  )
			return next->value;
		next = next->next;
	}
	return NULL;
}
