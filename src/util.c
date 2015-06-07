#include "util.h"
#include "definition.h"

// out put file
FILE * assembly_file;

// sections
char* bss_section;
char* data_section;
char* text_section;
char* current_function; 

/*
 *	VECTOR TO ALL SCOPES
 * */
Vector* scopes;
Function_table* functions;

/*
 *	Write a new asm file
 * */
void open_asm(char* file_name)
{
	char aux[100];
	sprintf(aux,"%s.asm",file_name);
	assembly_file = fopen(aux,"w+");
}

/*
 *	Used to close a file *.asm
 *	writting all sections initialized
 * */
void 
close_asm()
{
	close_text();
	if ( bss_section != NULL )
		fprintf(assembly_file,"%s",bss_section);
    if (data_section != NULL)
		fprintf(assembly_file,"%s",data_section);	
	if (text_section != NULL)
		fprintf(assembly_file,"%s",text_section);

	freeVector(scopes);
	fclose(assembly_file);
}

void 
init_bss()
{
	bss_section = malloc(1024*sizeof(char));
	strcpy(bss_section,"section .bss\n");
}

void 
init_data()
{
	data_section = malloc(1024*sizeof(char));
	strcpy(data_section,"section .data\n");
}

void 
init_text()
{
    int text_size = 10000;
	text_section = malloc(text_size * sizeof(char));
	
    strcpy(text_section,"section .text\n");
    
    strcat(text_section, "\tglobal main\n\n");
}

/*
 *	Initialize a asm context
 *
 * */
void 
init_asm(char* file_name)
{
	current_function = "global";
	scopes = newVector();
	functions = newFunctionTable(NULL,NULL,NULL,NULL);
	addSymbolTable(newSymbolTable(current_function),scopes);
	open_asm(file_name);
}

/*
 *  Analise a string data_type and return a type
 *
 * */
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

/*
 *  Get ptr_level from a string data_type
 *
 * */
int get_ptr_level(char* data_type)
{
	int count,i;
	for(count = 0,i=0; i < strlen(data_type);i++)	
		if (data_type[i] == '*') count++;
	return count;
}

/*
 *  Return a data_type from data_type string
 *
 * */
int 
get_data_type_id(char* data_type)
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

/*
 *
 *  Add symbol to some scope	
 *
 * */
void 
add_symbol_to_scopes(char* c_type,
					 char* string,
					 char* value,
					 int initialized)
{
		char error[128];
		int result = 0;
		int data_type = get_data_type_id(c_type);
		char* literal = extract_data_type(string);
		Symbol* current;

		switch( data_type)
		{
		case CHAR_T:
			current = newChar(literal,(char)value[1],initialized);
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

		if (!strcmp(current_function,"global")){
			result = validate_global_declaration(current,scopes);
			if (!result)
			{
				sprintf(error,"Global variable %s already declared.",current->name);
			}
		}else{
			result = validate_local_declaration(current,current_function,scopes);
			if (!result)
			{
				sprintf(error,"Local variable %s already declared.",current->name);
			}
		}
		
		if (result)
			addSymbolToScope(current_function,current,scopes);
		else
			yyerror(error);
}

/*	
 *	Append to bss a new constant
 *
 * */
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

/*
 *	Close bss section with all declarations
 *
 * */
void close_bss()
{
	init_bss();
	char variable[1000];
	SymbolTable* current = findTable("global",scopes); 
    while(current != NULL)
	{
        if(current->value->initialized == 0){
            declare_bss(current->value->name,
                current->value->data_type);
        }
        current = current->next;
	}
}

/*
 * Declare a data in data section
 *
 * */
void declare_data(char* name, int data_type)
{   
		char aux[20];
		sprintf(aux,"\t%s",name);
		strcat(data_section,aux);
		switch(data_type)
		{
		case CHAR_T: 
			strcat(data_section,": db 1 \n");break;
		case SHORT_T:
			strcat(data_section,": dw 1 \n");break;
		case INT_T:
			strcat(data_section,": dd 1 \n");break;
		case LONG_T:
			strcat(data_section, ": dd 1 \n");break;
		case FLOAT_T:
			strcat(data_section, ": dd 1 \n");break;
		case DOUBLE_T:
			strcat(data_section ,": dd 1 \n" );break;
		case PTR_T: 
			strcat(data_section,": dw 1 \n");break;
		}
}

/*
 * Close all data with all data declaration
 *
 * */
void close_data()
{
	init_data();
	char variable[1000];
	SymbolTable* current = findTable("global",scopes); 

    while(current != NULL)
	{   
        if(current->value->initialized == 1){
            switch(current->value->data_type){
                case CHAR_T:
                {
                    char aux[50];
                    sprintf(aux,"\t%s db \'%c\' \n", 
							current->value->name,
							current->value->char_value);
                    strcat(data_section,aux);
                    break;
                }
                case SHORT_T:
                    declare_data(current->value->name,
                                 current->value->data_type);
                    break;
                case INT_T:
                    declare_data(current->value->name,
                                 current->value->data_type);
                    break;
                case LONG_T:
                    declare_data(current->value->name,
                                 current->value->data_type);
                    break;
                case FLOAT_T:
                    declare_data(current->value->name,
                                 current->value->data_type);
                    break;
                case DOUBLE_T:
                    declare_data(current->value->name,
                                 current->value->data_type);
                    break;
                case PTR_T:
                    declare_data(current->value->name,
                                 current->value->data_type);
                    break;
            }
        }
        current = current->next;
    }
}

/*
 * Close a text section
 *
 * */
void close_text()
{
	finalize_stack();
}

/*
 *	Initialize e define a current function
 *
 * */
void 
initialize_functions(char* function_name,char* return_of_function)
{
	Function* newFunction=NULL;
	int result=0;
	char error[128];

	if (text_section == NULL) init_text();

  if((!strcmp(function_name,"main")))
  {
      strcat(text_section,"_start:\n");
      init_stack(1024);
  }
	else
	{
		finalize_stack();
		char aux[100];
		sprintf(aux,"%s:\n",function_name);
		strcat(text_section,aux);
		init_stack(1024);
	}

	result = function_was_declared(function_name,functions);
	if(!result)
	{
	 newFunction = new_function(get_data_type_id(return_of_function),
								function_name);
	 addSymbolTable(newSymbolTable(function_name),scopes);
	 addFunctionTable(newFunction,functions);
	 current_function = function_name;
	}
	else{
     sprintf(error,"The Function %s was previously declared.",function_name);
	 yyerror(error);
	}
}

/*
 * End a current function
 *
 * */
void 
end_function()
{
   current_function = "global";
}

/*
 *	Building a stack with size as parameter
 *
 * */
void init_stack(const int stack_size)
{
    char epilogue[100];
    
    sprintf(epilogue,"\tpush ebp\n\tmov ebp, esp\n\tsub esp, %d\n",stack_size);
    
    strcat(text_section, epilogue);
}

/*
 * Emptying stack in asm
 *
 * */
void finalize_stack()
{
	char prologo[100];
	sprintf(prologo,"\tmov esp, ebp\n\tpop ebp\n\tret\n");
	strcat(text_section,prologo);
}

/*
 *	Insert a data into a stack using asm 
 *
 * */
void 
push_to_stack(Data_type type)
{
	switch(type)
	{
		case CHAR_T:
		case SHORT_T:
			strcat(text_section,"\tpush word al\n");
		case INT_T:
		case FLOAT_T:
			strcat(text_section,"\tpush word ax\n");
			break;
		case DOUBLE_T:
		case LONG_T:
		case PTR_T:
			strcat(text_section,"\tpush eax\n");
			break;
	}
}

/* TODO: FIX DOUBLE LITERAL NUMBERS */
void
push_to_operand_stack(Data_type type, int is_literal, const char* operand) {
	printf("OPERAND STACK FUNCTION\n");
    int result;
	char instruction[300];
	char aux[100];
	int four_bytes_operand = (type == DOUBLE_T || type == LONG_T || type == PTR_T);
	if(is_literal) {
		sprintf(instruction, "\tmov eax, %s\n", operand);
		sprintf(aux, "%s", four_bytes_operand ? "\tpush eax\n" : "\tpush word ax\n");
	} else {
		sprintf(instruction, "\txor eax, eax\n");
        result = get_variable_position(operand);
		read_variable(type,result);
		sprintf(aux, "%s", four_bytes_operand ? "\tpush eax\n" : "\tpush word ax\n");
	}
	strcat(instruction, aux);
	strcat(text_section, instruction);
	strcat(text_section, "\n");
}

/* RETURNS THE VARIABLE POSITION IN THE SYMBOL TABLE IN BYTES */
int
get_variable_position(char* name) {
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
get_variable_data_type(const char* name) {
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
	printf("ERRO, VARIÁVEL NÃO ENCONTRADA NA TABELA");
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

/*
 * Function used to read a variable in asm from stack
 *
 * */
void
read_variable(Data_type type, int offset)
{
	char aux[100];
	switch(type)
	{
		case CHAR_T:
		case SHORT_T:
			sprintf(aux,"\tmov al, BYTE [esp + %d]\n",offset);
			break;
		case INT_T:
		case FLOAT_T:
			sprintf(aux,"\tmov ax, WORD [esp + %d]\n",offset);
			break;
		case DOUBLE_T:
		case LONG_T:
		case PTR_T:
			sprintf(aux,"\tmov eax, [esp + %d]\n",offset);
			break;
	}
	strcat(text_section,aux);
}

void add() {

}

void sub() {

}

void mult() {

}

void _div() {
	
}
