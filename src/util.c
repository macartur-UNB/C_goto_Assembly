#include "util.h"
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

void init_text()
{
    int text_size = 10000;
	text_section = malloc(text_size * sizeof(char));
	
    strcpy(text_section,"section .text\n");
    
    strcat(text_section, "\tglobal _start\n\n");
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


		result = validate_symbol_declaration(current,scope,scopes);
		if (!result)
		{
			char error[100];
			sprintf(error,"Variable %s already declared.",current->name);
			yyerror(error);
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

void close_bss()
{
	init_bss();
	char variable[1000];
	SymbolTable* current = findTable("__global",scopes); 
    while(current != NULL)
	{
        if(current->value->initialized == 0){
            declare_bss(current->value->name,
                current->value->data_type);
        }
        current = current->next;
	}
}

void declare_data(char* name, int data_type)
{   
		char aux[20];
		sprintf(aux,"\t%s",name);
		strcat(data_section,aux);
		switch(data_type)
		{
		case CHAR_T: 
			strcat(data_section," db 1 \n");break;
		case SHORT_T:
			strcat(data_section," dw 1 \n");break;
		case INT_T:
			strcat(data_section," dd 1 \n");break;
		case LONG_T:
			strcat(data_section, " dd 1 \n");break;
		case FLOAT_T:
			strcat(data_section, " dd 1 \n");break;
		case DOUBLE_T:
			strcat(data_section ," dd 1 \n" );break;
		case PTR_T: 
			strcat(data_section," dw 1 \n");break;
		}
}

void close_data()
{
	init_data();
	char variable[1000];
	SymbolTable* current = findTable("__global",scopes); 
    while(current != NULL)
	{   
        if(current->value->initialized == 1){
            switch(current->value->data_type){
                case CHAR_T:
                {
                    char aux[50];

                    sprintf(aux,"\t%s db \'%c\' \n", current->value->name, current->value->char_value);
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

void close_text()
{

}

void declarate_data(char* name, int data_type, void* value)
{
	init_data();
}

void initialize_functions(const char* function_name)
{
    if((!strcmp(function_name,"main")) && (text_section == NULL))
    {
        init_text();
        
        strcat(text_section,"_start:\n");
        
        init_stack(30);
    }
}

void init_stack(const int stack_size)
{
    char epilogue[100];
    
    sprintf(epilogue, "\tpush ebp\n\tmov ebp, esp\n\tsub esp, %d\n",stack_size);
    
    strcat(text_section, epilogue);
}

void finalize_stack()
{
	char prologo[100];
	sprintf(prologo,"\tmov esp, ebp\n\tpop ebp");;
	strcat(text_section,prologo);
}

/*      valor  type         */
void push_to_stack(Data_type type)
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

/*   type posicao  */
void read_variable(Data_type type,int offset)
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




int 
validate_symbol_declaration(Symbol* symbol,char* scope,Vector* scopes)
{
	SymbolTable* current = findTable(scope,scopes); 
    while(current != NULL)
	{
		Symbol* s = current->value;
		if( s != NULL)
		{
			if ( ! strcmp(s->name,symbol->name)  )
				return 0;
		}
        current = current->next;
	}
	return 1;
}
