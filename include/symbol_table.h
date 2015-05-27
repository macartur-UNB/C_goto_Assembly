#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "symbol.h"

typedef struct SymbolTable
{
    char*               		scope;	
    struct SymbolTable*        	head;
    struct SymbolTable*        	tail;
    Symbol*             		value;
    struct SymbolTable*        	next;
}SymbolTable;

SymbolTable* newSymbolTable(char* scope);
void addSymbol( Symbol * symbol,SymbolTable* symbol_table);
void freeSymbolTable(SymbolTable * symbol_table);

Symbol* findSymbol  (char* name,SymbolTable* symbol_table);
SymbolTable*
createSymbolTable(char* scope, SymbolTable* head, SymbolTable* tail,Symbol* value,SymbolTable* next);


size_t get_position_stack(Symbol* symbol);


#endif
