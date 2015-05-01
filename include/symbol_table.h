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

// method to add a generic new symbol in a symbol_table
void addSymbol( Symbol * symbol,SymbolTable* symbol_table);
// method used to print a table values
void printTable(SymbolTable* table);
// method to free a variable from struct symbol_table
void freeSymbolTable(SymbolTable * symbol_table);

// find symbol in a symbol_table
Symbol* findSymbol  (char* name,SymbolTable* symbol_table);
Symbol* findChar	(char* name, char char_value,SymbolTable* symbol_table);
Symbol* findShort	(char* name, short short_value,SymbolTable* symbol_table);
Symbol* findInt		(char* name, int int_value,SymbolTable* symbol_table);
Symbol* findLong	(char* name, long long_value,SymbolTable* symbol_table);
Symbol* findFloat	(char* name, float float_value,SymbolTable* symbol_table);
Symbol* findDouble	(char* name, double double_value,SymbolTable* symbol_table);
Symbol* findPoiter	(char* name, unsigned int ptr_level, Data_type ptr_type,
					 void* ptr_value,SymbolTable* symbol_table);

// create to generate a generic symbol_table empty
SymbolTable* 
createSymbolTable(char* scope, SymbolTable* head, SymbolTable* tail,
									 Symbol* value,SymbolTable* next);

#endif
