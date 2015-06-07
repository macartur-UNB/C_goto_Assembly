#ifndef VALIDADE_H
#define VALIDADE_H

#include "symbol.h"
#include "symbol_table.h"
#include "vector.h"
#include "function.h"
#include "function_table.h"



/*
 *  VALIDATE FUNCTIONS
 *
 * */

int function_was_declared(char* function_name,Function_table* functions);
int validate_return_of_function(char* function_name,
                                Data_type return_of_function,
                                Function_table* functions);

/*
 *
 *  VALIDATE SCOPES
 *
 * */
int validate_local_declaration(Symbol* symbol,char* scope,
						       Vector* scopes);
int validate_global_declaration(Symbol* symbol,Vector* scopes);
int validate_symbol_declaration(Symbol* symbol,char* scope,Vector* scopes);
#endif
