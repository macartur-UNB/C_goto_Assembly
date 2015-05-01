#ifndef VECTOR_H
#define VECTOR_H

#include "symbol_table.h"
#include "symbol.h"

typedef struct Vector
{
    unsigned int size;
    unsigned int capacity;
    SymbolTable** tables;
}Vector;


Vector* newVector();
void reallocVector(Vector* vector);
void addSymbolTable(SymbolTable* symbol_table, Vector* vector);
void addSymbolToScope(char* scope,Symbol* symbol,Vector* vector );
void freeVector(Vector* vector);

SymbolTable* findTable(char* scope,Vector* vector);
Symbol* findSymbolFromVector(char* scope,char* name,Vector* vector);
int canAddAtScope(char* scope,Symbol* symbol, Vector* vector);

#endif
