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
 *
 * */
void add_symbol_to_scopes(char* c_type,
						  char* string,
						  char* value,
						  int initialized,
						  char* scope);
void declare_bss(char* name,int type);
void declarate_data(char* name, int data_type, void* value);

/*
 *	EXTRACT INFORMATION FROM STRING
 *
 * */
int get_ptr_level(char* data_type);
int data_type_id(char* data_type);
char* extract_data_type( char* data_type);
#endif
