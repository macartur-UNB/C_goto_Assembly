#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Vector* 
newVector()
{
	Vector* v = (Vector*)malloc(sizeof(Vector));
	v->size 		= 0;
	v->capacity 	= 2;
	v->tables	 	= (SymbolTable**) calloc ( 2 ,sizeof(SymbolTable*));

	return v; 
}

void 
reallocVector(Vector* vector)
{
    size_t new_capacity = vector->capacity*2;
	vector->tables = (SymbolTable**) realloc((void*)vector->tables, new_capacity*sizeof(SymbolTable*));	
	vector->capacity = new_capacity;
}


void 
addSymbolTable(SymbolTable* symbol_table, Vector* vector)
{
	if ( vector->size+1 >= vector->capacity)
		reallocVector(vector);
	vector->tables[vector->size] = symbol_table;
	vector->size++;
}

void freeVector(Vector* vector)
{
	while(vector->size != -1)
	{
		freeSymbolTable(vector->tables[vector->size]);
		vector->size--;
	}
	free(vector);
}

SymbolTable*
findTable(char* scope,Vector* vector)
{
	if(vector->size == 0 && vector->tables[0] == NULL) 
	{
		return NULL;
	}
	int count = 0;	

	while(  count < vector->size)	
	{
		if (!strcmp(vector->tables[count]->scope,scope))
		{
			SymbolTable* t = vector->tables[count];
			return t; 
		}
		count++;
	}
	return NULL;
}

Symbol*
findSymbolFromVector(char* scope, char* name,Vector* vector)
{
	if(scope == NULL || name == NULL || vector == NULL)
		return NULL;
	SymbolTable* table = findTable(scope,vector);

	if (table == NULL)
		printf("NULL TABLE");


	return findSymbol( name ,table );
}

void 
addSymbolToScope(char* scope,Symbol* symbol,Vector* vector )
{
	SymbolTable* table = findTable(scope,vector);
	if (table  != NULL ){
		addSymbol(symbol,table);
	}
}

int 
canAddAtScope(char* scope,Symbol* symbol, Vector* vector)
{
	SymbolTable* table = findTable(scope,vector);
	if(!table )	return 0;

	if( table->head == NULL  )
		return 1;

	Symbol*s = findSymbol( symbol->name  ,table  );
	if(!s)
		return 1;

	return 0;
}
