#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "symbol_table.h"
#include "symbol.h"
#include "validate.h"
#include "logic_operation.h"


/*
 *
 *	INITIALIZES FUNCTIONS
 *
 * */
void init_asm();
void init_bss();
void init_data();
void init_text();
void include_extern_asm();

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
 *	EXTRACT INFORMATION FROM STRING
 *
 * */
int get_ptr_level(char* data_type);
int data_type_id(char* data_type);
char* extract_data_type( char* data_type);

/*
 *	Proxy Operations
 * */
void make_operation(int operation);


#endif
