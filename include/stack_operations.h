#ifndef STACK_OPERATIONS
#define STACK_OPERATIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "symbol_table.h"
#include "symbol.h"
#include "validate.h"

/*
 *	OPERAND_STACK
 *
 *
 * */
void init_stack(char* text_section);
void finalize_stack(char* text_section);
void push_char_to_stack(char* text_section,char* text);	
void push_int_to_stack(char* text_section,char* text);
void push_double_to_stack(char* text_section,char* text);
void push_float_to_stack(char* text_section,char* text);
void push_variable_to_stack(char* text_section,char* text);
int  get_variable_position(char* name,char* current_function,Vector* scopes);
Data_type get_variable_data_type(const char* name, char* current_function,Vector* scopes);
void assign(char* variable);
int get_variable_size(Data_type type);
#endif
