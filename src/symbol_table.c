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
	return createSymbolTable(scope,NULL,NULL,NULL,NULL,NULL);
}


SymbolTable* 
createSymbolTable(char* scope, SymbolTable* head, SymbolTable* tail,
									 Symbol* value,SymbolTable* prev,SymbolTable* next  )
{
	SymbolTable* result = (SymbolTable*) malloc(sizeof(SymbolTable)); 

	result->scope = scope;
	result->head =  head;
	result->tail =  tail;
	result->value = value;
	result->next =  next;
	result->prev =  prev;

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
		symbol_table->prev = NULL;
		symbol_table->next = NULL;
		return;
	}

	SymbolTable* next = createSymbolTable(symbol_table->scope,
										  symbol_table->head,
                                          symbol_table->tail,
                                          symbol,
										  NULL,
										  NULL);
	next->prev = symbol_table->tail;
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
		if( !strcmp(next->value->name,name)  )
			return next->value;
		next = next->next;
	}
	return NULL;
}

size_t
get_position_stack(Symbol*symbol)
{
	// TODO: duplamente encadeada 
	return 0;	
}

/*
 *	Print symbol table from left to right
 * */
void 
print_table_LR(SymbolTable* symbol_table)
{
	SymbolTable* current = symbol_table;
	printf("Symbol[");
	while( current->next != NULL)
	{
		Symbol* s = current->value;
		printf(" %s ",s->name);
		current = current->next;
	}
	printf("]\n");
}

/*
 *	Print symbol table from right to left
 * */
void 
print_table_RL(SymbolTable* symbol_table)
{
	SymbolTable* current = symbol_table->tail;
	printf("Symbol[");
	while( current->prev != NULL)
	{
		Symbol* s = current->value;
		printf(" %s ",s->name);
		current = current->prev;
	}
	printf("]\n");
}
