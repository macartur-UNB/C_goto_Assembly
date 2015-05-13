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
	open_asm();
	if ( bss_section != NULL )
		fprintf(assembly_file,"%s",bss_section);
    if (data_section != NULL)
		fprintf(assembly_file,"%s",data_section);	
	if (text_section != NULL)
		fprintf(assembly_file,"%s",text_section);

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
	char global[25];
	int text_size = 10000;
	text_section = malloc(text_size*sizeof(char));
	strcpy(text_section,"section .text\n");
	sprintf(global,"\tglobal %s\n",global_section);
	strcat(text_section,global);
}

void init_asm()
{
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
		if (data_type[i] == ' '||
			data_type[i] == ';'	) break;
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

void add_symbol_to_scopes(char* c_type,
						  char* string,
						  char* value,
						  int initialized,
						  char* scope)
{
		int data_type = get_data_type_id(c_type);
		char* literal = extract_data_type(string);
		Symbol* current;

		switch( data_type)
		{
		case CHAR_T:
			current = newChar(literal,(char)value[0],initialized);
			break;
		case SHORT_T:
			current = newShort(literal,(int)atoi(value),initialized);
			break;
		case INT_T:
			current = newInt(literal,atoi(value),initialized);
			break;
		case DOUBLE_T:
			current = newDouble(literal,strtod(value,NULL),initialized); 
			break;
		case FLOAT_T:
			current = newFloat(literal,atof(value),initialized);
			break;
		case LONG_T:
			current = newLong(literal,strtol(value,NULL,10),initialized);
			break;
		case PTR_T:
			/*
			 *		TODO 				
			 *		*/
			break;
		}	
		addSymbolToScope(scope,current,scopes);
}



void declare_bss(char* name, int data_type)
{
		char aux[20];
		sprintf(aux,"\t%s",name);
		strcat(bss_section,aux);
		switch(data_type)
		{
		case CHAR_T: 
			strcat(bss_section," resb 1 \n");break;
		case SHORT_T:
			strcat(bss_section," resw 1 \n");break;
		case INT_T:
			strcat(bss_section," resw 1 \n");break;
		case LONG_T:
			strcat(bss_section, " resd 1 \n");break;
		case FLOAT_T:
			strcat(bss_section, " resd 1 \n");break;
		case DOUBLE_T:
			strcat(bss_section ," resd 1 \n" );break;
		case PTR_T: 
			strcat(bss_section," resw 1 \n");break;
		}
}

void
close_bss()
{
	init_bss();
	char variable[1000];
	SymbolTable* current = findTable("__global",scopes); 
	while(current != NULL)
	{
		declare_bss(current->value->name,
					current->value->data_type);
		current = current->next;
	}
}

void
close_data()
{
	
}
void close_text()
{

}

void 
declarate_data(char* name, int data_type, void* value)
{
	init_data();
}


