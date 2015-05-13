#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdlib.h>

typedef enum  { CHAR_T, SHORT_T, INT_T, LONG_T, FLOAT_T, DOUBLE_T, PTR_T } Data_type;

typedef struct  Symbol
{
    Data_type data_type;
    char* name;
    int initialized;
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

Symbol* newChar		(char* name, char char_value,int initialized);
Symbol* newShort	(char* name, short short_value,int initialized);
Symbol* newInt		(char* name, int int_value,int initialized);
Symbol* newLong		(char* name, long long_value,int initialized);
Symbol* newFloat	(char* name, float float_value,int initialized);
Symbol* newDouble	(char* name, double double_value,int initialized);
Symbol* newPoiter	(char* name, unsigned int ptr_level, Data_type ptr_type,void* ptr_value,int initialized);

Symbol* createSymbol();
void freeSymbol(Symbol* symbol);
#endif
