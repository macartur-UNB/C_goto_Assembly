#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdlib.h>

/*
 *   Values used to represent a type of data stored in a symbol
 * */
typedef enum  { CHAR_T, SHORT_T, INT_T, LONG_T, FLOAT_T, DOUBLE_T, PTR_T } Data_type;

/*
 *  Struct used to represent a symbol 
 * */
typedef struct  Symbol
{
    Data_type data_type;
    char* name;
    unsigned int ptr_level;
    Data_type ptr_type;
    union{
        char        char_value;
        short       short_value;
        int         int_value;
        long        long_value;
        float       float_value;
        double      double_value;
        void*       ptr_value;
    };
} Symbol;

// function used to free a poiter used in a symbol
void freeSymbol(Symbol* symbol);

// functions used to create a new symbol 
Symbol* newChar		(char* name, char char_value);
Symbol* newShort	(char* name, short short_value);
Symbol* newInt		(char* name, int int_value);
Symbol* newLong		(char* name, long long_value);
Symbol* newFloat	(char* name, float float_value);
Symbol* newDouble	(char* name, double double_value);
Symbol* newPoiter	(char* name, unsigned int ptr_level, Data_type ptr_type,
					 void* ptr_value);

//   function used to alloc a symbol space
Symbol* createSymbol();
#endif
