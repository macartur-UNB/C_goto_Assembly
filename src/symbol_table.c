#include <stdlib.h>
#include "symbol_table.h"


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
		result->head =  (SymbolTable*)head;
	}
	
	if (! tail )
	{
		result->tail = NULL;
	}
	else
	{
		result->tail =  (SymbolTable*)tail;
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
		result->next =  (SymbolTable*)next;
	}	

	return result; 
}

void 
addSymbol(SymbolTable* symbol_table, Symbol * symbol)
{
	if( symbol_table->head == NULL )		
		symbol_table->value = symbol;
		symbol_table->head =  (SymbolTable*)symbol_table;
		symbol_table->tail =  (SymbolTable*)symbol_table;
	}
		// pega o ultimo elemento para colocar o simbolo como ultimo elemento
		SymbolTable* head = (SymbolTable*) symbol_table->head;
		SymbolTable* tail = (SymbolTable*) symbol_table->head->tail;

		//   sem escopo, sem head, sem tail , value, sem next
		SymbolTable* next = createSymbolTable(NULL,NULL,NULL,symbol,NULL);
		head->tail = next;
		tail->next = next;
}

void 
FreeSymbolTable(SymbolTable * symbol_table)
{
	while( symbol_table->next )
	{
		freeSymbol(symbol_table->value);
		SymbolTable* next = (SymbolTable*) symbol_table->next;
		free(symbol_table);
		symbol_table = next;
	}
	symbol_table	= NULL;
}
