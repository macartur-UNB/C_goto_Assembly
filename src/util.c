#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "symbol_table.h"
#include "symbol.h"
#include "definitions.h"

// out put file
FILE * assembly_file;

// sections
char* bss_section;
char* data_section;
char* text_section;

/*
 *	VECTOR TO ALL SCOPES
 * */
Vector* scopes;


void open_asm()
{
	assembly_file = fopen("main.asm","w+");
}

void close_asm()
{
	if ( bss_section != NULL )
		fprintf(assembly_file,"%s",bss_section);
    if (data_section != NULL)
		fprintf(assembly_file,"%s",data_section);	
	if (text_section != NULL)
		fprintf(assembly_file,"%s",text_section);
	/*  free all symbols*/
	freeVector(scopes);
	fclose(assembly_file);
}

void init_bss()
{
	bss_section = malloc(1024*sizeof(char));
	strcpy(bss_section,"section .bss\n");
}

void init_data()
{
	data_section = malloc(1024*sizeof(char));
	strcpy(data_section,"section .data\n");
}

void init_text(char* global_section)
{
	int text_size = 10000;
	text_section = malloc(text_size*sizeof(char));
	strcpy(text_section,"section .text\n");
	sprintf(text_section,"\tglobal %s",global_section);
}

void init_asm()
{
	open_asm();
	scopes = newVector();
	addSymbolTable(newSymbolTable("__global"),scopes);
}


char* extract_data_type(char* data_type)
{
    char* result;
	int i,k;
	k = strlen(data_type);
	result = (char*) malloc(k*sizeof(char));
	for(i=0;i<k;i++)
	{
		if (data_type[i] == ' ') break;
		result[i] = data_type[i];
	}
	result[i] = '\0';

	return result;
}
int get_ptr_level(char* data_type)
{
	int count,i;
	for(count = 0,i=0; i < strlen(data_type);i++)	
		if (data_type[i] == '*') count++;
	return count;
}

int get_data_type_id(char* data_type)
{
	char* type = extract_data_type(data_type);
	int i;
	if (get_ptr_level(type)>0) return PTR_T;

	char* all_types[] = {"char","short",
						"int","long",
						"float","double"};
	for (i=0;i<7;i++)
		if ( ! strcmp(all_types[i],type))
			return i;

	return -1;
}
void add_symbol_to_scopes(char* c_type,char* string,char* value,char* scope)
{
		int data_type = get_data_type_id(c_type);
		Symbol* current;

		switch( data_type)
		{
		case CHAR_T:
			current = newChar(string,(char)value[0]);
			break;
		case SHORT_T:
			current = newShort(string,(int)atoi(value));
			break;
		case INT_T:
			current = newInt(string,atoi(value));
			break;
		case DOUBLE_T:
			current = newDouble(string,strtod(value,NULL)); 
			break;
		case FLOAT_T:
			current = newFloat(string,atof(value));
			break;
		case LONG_T:
			current = newLong(string,strtol(value,NULL,10));
			break;
		case PTR_T:
			/*
			 *		TODO 				
			 *		*/
			break;
		}	
		addSymbolToScope(scope,current,scopes);
}
void
close_bss()
{
	SymbolTable* current = findTable("__global",scopes); 
	if(!current)
		printf("NULL");
}
