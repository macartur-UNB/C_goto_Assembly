#ifndef UTIL_H
#define UTIL_H

/*
 *
 *	INITIALIZES FUNCTIONS
 *
 * */
void init_asm();
void init_bss();
void init_data();
void init_text();
void open_asm();
void close_asm();
void close_bss();

/*
 *
 *	FUNCTIONS TO INCREMENT A SECTION
 *
 *
 * */
void add_symbol_scopes();
//void add_bss_section(Symbol* symbol);
//void get_type_of_symbol();

/*
 *	EXTRACT INFORMATION FROM STRING
 *
 * */
int get_ptr_level(char* data_type);
int data_type_id(char* data_type);
char* extract_data_type( char* data_type);
#endif
