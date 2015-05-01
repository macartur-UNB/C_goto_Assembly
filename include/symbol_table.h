#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "symbol.h"


typedef struct SymbolTable_t
{
    char*               scope;
    struct SymbolTable*        head;
    struct SymbolTable*        tail;
    Symbol*             value;
    struct SymbolTable*        next;
}SymbolTable;

/*
typedef struct vector{
    table;
}
*/

SymbolTable* createSymbolTable();

void addSymbol(SymbolTable* symbol_table, Symbol * symbol);
void FreeSymbolTable(SymbolTable * symbol_table);

#endif
