#include "stack_operations.h"

typedef enum {DB,DW,DD} TYPE_TOP_STACK;
int type_of_top_stack = 0;
int alternate_register = 0;

void init_stack(char* text_section)
{
	char* epilogue = (char*)malloc(sizeof(char)*100);
    
    sprintf(epilogue,"\tpush ebp\n\tmov ebp, esp\n");
	strcat(text_section,epilogue);
	free(epilogue);
	type_of_top_stack = 0;
}

void 
finalize_stack(char* text_section)
{
	char* prologo = (char*)malloc(sizeof(char)*100);
	sprintf(prologo,"\tmov esp, ebp\n\tpop ebp\n");
	strcat(text_section,prologo);
	free(prologo);
}

void next_register(){
	alternate_register = (alternate_register++)%2;	
}


void push_char_to_stack(char* text_section,char* text)	
{
	char* text_aux = (char*)malloc(sizeof(char)*100);
	char character= text[0];	
    sprintf(text_aux,"\tpush db %c\n",character); 
	strcat(text_section,text_aux);
		
	type_of_top_stack = DB;
	next_register();
}

void
push_int_to_stack(char* text_section,char* text)
{
	char* text_aux = (char*)malloc(sizeof(char)*100);
	int value= atoi(text);	
    sprintf(text_aux,"\tpush DWORD %d\n",value); 
	strcat(text_section,text_aux);
	type_of_top_stack = DW;
	next_register();
}

void
push_float_to_stack(char* text_section,char* text)
{
	char* text_aux = (char*)malloc(sizeof(char)*100);
	float value= atof(text);	
    sprintf(text_aux,"\tpush DWORD %f\n",value); 
	strcat(text_section,text_aux);
	type_of_top_stack = DW;
	next_register();
}


void
push_double_to_stack(char* text_section,char* text)
{
	char* text_aux = (char*)malloc(sizeof(char)*100);
	double value= atof(text);	
    sprintf(text_aux,"\tpush DD %f\n",value); 
	strcat(text_section,text_aux);
	type_of_top_stack = DD;
	next_register();
}

void 
push_variable_to_stack(char* text_section,char* text)
{
}

void
sum_and_push(char* text_section)
{
	char* text =(char*)malloc(sizeof(char)*200);
	switch(type_of_top_stack)
	{
		case DB:
			sprintf(text,"\tpop ebx\n");
			strcat(text,"\tpop eax\n");
			strcat(text,"\tadd eax, ebx\n");
			strcat(text,"\tpush DB eax\n");
		    break;	
		case DW:
			sprintf(text,"\tpop ebx\n");
			strcat(text,"\tpop eax\n");
			strcat(text,"\tadd eax, ebx\n");
			strcat(text,"\tpush DWORD eax\n");
			break;
		case DD:
			sprintf(text,"\tpop ebx\n");
			strcat(text,"\tpop eax\n");
			strcat(text,"\tadd eax, ebx\n");
			strcat(text,"\tpush DD eax\n");
			break;
	}
	strcat(text_section,text);
}

void
sub_and_push(char* text_section)
{
	char* text =(char*)malloc(sizeof(char)*200);
	switch(type_of_top_stack)
	{
		case DB:
			sprintf(text,"\tpop ebx\n");
			strcat(text,"\tpop eax\n");
			strcat(text,"\tsub eax, ebx\n");
			strcat(text,"\tpush DB eax\n");
		    break;	
		case DW:
			sprintf(text,"\tpop ebx\n");
			strcat(text,"\tpop eax\n");
			strcat(text,"\tsub eax, ebx\n");
			strcat(text,"\tpush DWORD eax\n");
			break;
		case DD:
			sprintf(text,"\tpop ebx\n");
			strcat(text,"\tpop eax\n");
			strcat(text,"\tsub eax, ebx\n");
			strcat(text,"\tpush DD eax\n");
			break;
	}
	strcat(text_section,text);
}

void
mult_and_push(char* text_section)
{
	char* text =(char*)malloc(sizeof(char)*200);
	switch(type_of_top_stack)
	{
		case DB:
			sprintf(text,"\tpop ebx\n");
			strcat(text,"\tpop eax\n");
			strcat(text,"\tmul ebx\n");
			strcat(text,"\tpush DB eax\n");
		    break;	
		case DW:
			sprintf(text,"\tpop ebx\n");
			strcat(text,"\tpop eax\n");
			strcat(text,"\tmul ebx\n");
			strcat(text,"\tpush DWORD eax\n");
			break;
		case DD:
			sprintf(text,"\tpop ebx\n");
			strcat(text,"\tpop eax\n");
			strcat(text,"\tmul ebx\n");
			strcat(text,"\tpush DD eax\n");
			break;
	}
	strcat(text_section,text);
}
void
div_and_push(char* text_section)
{
	char* text =(char*)malloc(sizeof(char)*200);
	switch(type_of_top_stack)
	{
		case DB:
			sprintf(text,"\tpop ebx\n");
			strcat(text,"\tpop eax\n");
			strcat(text,"\tdiv ebx\n");
			strcat(text,"\tpush DB eax\n");
		    break;	
		case DW:
			sprintf(text,"\tpop ebx\n");
			strcat(text,"\tpop eax\n");
			strcat(text,"\tdiv ebx\n");
			strcat(text,"\tpush DWORD eax\n");
			break;
		case DD:
			sprintf(text,"\tpop ebx\n");
			strcat(text,"\tpop eax\n");
			strcat(text,"\tdiv ebx\n");
			strcat(text,"\tpush DD eax\n");
			break;
	}
	strcat(text_section,text);
}
void
mod_and_push(char* text_section)
{
	char* text =(char*)malloc(sizeof(char)*200);
	switch(type_of_top_stack)
	{
		case DB:
			sprintf(text,"\tpop ebx\n");
			strcat(text,"\tpop eax\n");
			strcat(text,"\tdiv ebx\n");
			strcat(text,"\tmov eax,edx\n");
			strcat(text,"\tpush DB eax\n");
		    break;	
		case DW:
			sprintf(text,"\tpop ebx\n");
			strcat(text,"\tpop eax\n");
			strcat(text,"\tdiv ebx\n");
			strcat(text,"\tmov eax,edx\n");
			strcat(text,"\tpush DWORD eax\n");
			break;
		case DD:
			sprintf(text,"\tpop ebx\n");
			strcat(text,"\tpop eax\n");
			strcat(text,"\tdiv ebx\n");
			strcat(text,"\tmov eax,edx\n");
			strcat(text,"\tpush DD eax\n");
			break;
	}
	strcat(text_section,text);
}


int
get_variable_position(char* name,char* current_function,Vector* scopes) {
    SymbolTable* symbol_table = findTable(current_function, scopes);
    if (!symbol_table) {
        exit(EXIT_FAILURE);
    }
    SymbolTable* current = symbol_table->tail;
    Symbol* s;
    int counter = 0;
    while(current->prev != NULL)
    {
        s = current->value;
        counter += get_variable_size(current->value->data_type);
        if(!strcmp(s->name, name)) {
            return counter;
        }
        current = current->prev;
    }

    return -1;
}

Data_type
get_variable_data_type(const char* name, char* current_function,Vector* scopes) {
    SymbolTable* symbol_table = findTable(current_function, scopes);
    if (!symbol_table) {
        printf("ERRO TABELA NULA\n");
        exit(EXIT_FAILURE);
    }
    SymbolTable* current = symbol_table->tail;
    Symbol* s;
    while(current->prev != NULL)
    {
        s = current->value;
        printf("%s\n", s->name);
        if(!strcmp(s->name, name)) {
            return s->data_type;
        }
        current = current->prev;
    }
    exit(EXIT_FAILURE);
}


int
get_variable_size(Data_type type) {
    switch(type)
    {
        case CHAR_T:
        case SHORT_T:
        case INT_T:
        case FLOAT_T:
            return 2;
        case DOUBLE_T:
        case LONG_T:
        case PTR_T:
            return 4;
    }
}

