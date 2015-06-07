#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "symbol_table.h"
#include "symbol.h"
#include "validate.h"


/*
 *
 *	INITIALIZES FUNCTIONS
 *
 * */
void init_asm();
void init_bss();
void init_data();
void init_text();

/*
 *	Open and Close file nasm
 * */
void open_asm();
void close_asm();
/**
 *
 *	ENDING ALL SECTIONS
 *
 * */
void close_bss();  
void close_data();
void close_text();

/*
 *
 *	FUNCTIONS TO INCREMENT A SECTION
 *
 * */
void add_symbol_to_scopes(char* c_type,
						  char* string,
						  char* value,
						  int initialized);
void declare_bss(char* name,int type);
void declarate_data(char* name, int data_type, void* value);

/*
 *	OPERAND_STACK
 *
 *
 * */

void init_stack(const int stack_size);
void finalize_stack();
void push_to_stack(Data_type type);
void read_variable(Data_type type,int offset);
Data_type get_variable_data_type(const char* name);
void push_to_operand_stack(Data_type type, int is_literal, const char* operand);
/*
 *	EXTRACT INFORMATION FROM STRING
 *
 * */
int get_ptr_level(char* data_type);
int data_type_id(char* data_type);
char* extract_data_type( char* data_type);
#endif
