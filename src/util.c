#include "util.h"
#include "definition.h"

// out put file
FILE * assembly_file;

// sections
char* bss_section;
char* data_section;
char* text_section;
char* header_section;
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

	if (header_section != NULL)
		fprintf(assembly_file,"%s",header_section);
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
	include_extern_asm();
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
            /*  TODO: fix it*/
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
		case INT_T:
			strcat(bss_section," resw 1 \n");break;
		case LONG_T:
		case FLOAT_T:
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
		case LONG_T:
		case FLOAT_T:
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
	finalize_stack(text_section);
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
	char aux[100];
	char* text = NULL;

	if (text_section == NULL) init_text();

    if((!strcmp(function_name,"main")))
    {
      strcat(text_section,"main:\n");
      init_stack(text_section);
    }
	else
	{
		finalize_stack(text_section);
		sprintf(aux,"%s:\n",function_name);
		strcat(text_section,aux);
		init_stack(text_section);
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

void include_extern_asm(){
	header_section = (char*) malloc(sizeof(char)*1000);
	strcat(header_section,"extern printf\n");
	strcat(header_section,"extern scanf\n");
}

void push_to_stack(char* text,int type){
	switch(type)
	{
	case 0:	push_variable_to_stack(text_section,text);break;
	case 1: push_char_to_stack(text_section,text);break;
	case 2: push_int_to_stack(text_section,text);break;
	case 3:	push_float_to_stack(text_section,text);break;
	case 4:	push_double_to_stack(text_section,text);break;
	default:
		break;
	}
}
void
make_operation(int operation)
{
	switch(operation)
	{
	case 0:	sum_and_push(text_section);    break;
	case 1: sub_and_push(text_section);    break;
	case 2: mult_and_push(text_section);   break;
	case 3:	div_and_push(text_section);    break;
	case 4:	mod_and_push(text_section);    break;
	default:
		break;
	}
}
