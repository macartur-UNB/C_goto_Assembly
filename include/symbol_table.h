#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "symbol.h"

/*
 *	Struct to represent a symbol table used to store 
 *	a global variable or a local variable.
 * */
typedef struct SymbolTable
{
    char*               		scope;	/*  global or name of function */
    struct SymbolTable*        	head;
    struct SymbolTable*        	tail;
    Symbol*             		value;
    struct SymbolTable*        	next;
}SymbolTable;

// Builder to create a empty symbol table
SymbolTable* newSymbolTable(char* scope);

// function to add a generic new symbol in a symbol_table
void addSymbol( Symbol * symbol,SymbolTable* symbol_table);

// function to free a variable from struct symbol_table
void freeSymbolTable(SymbolTable * symbol_table);

// find symbol in a symbol_table
Symbol* findSymbol  (char* name,SymbolTable* symbol_table);

// create to generate a generic symbol_table empty
SymbolTable* 
createSymbolTable(char* scope, SymbolTable* head, SymbolTable* tail,
									 Symbol* value,SymbolTable* next);

#endif
