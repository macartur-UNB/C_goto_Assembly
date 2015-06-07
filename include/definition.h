#ifndef DEFINITION_H
#define DEFINITION_H
#include <stdio.h>


/*
 *	TYPE OF FILE
 *	STDIN  = INPUT FILE
 *	STDOUT = OUTPUT FILE
 *	STDERR = ERROR FILE
 *
 * */
typedef enum {STDIN, STDOUT, STDERR} FileDescriptor;

/*
 *	TYPE OF CALLS
 *
 * */
typedef enum { SYS_EXIT, SYS_FORK, 
			   SYS_READ, SYS_WRITE,
               SYS_OPEN, SYS_CLOSE 
			 } Call;

/**
 *  REGISTER IN ASM
 *  eax = SYS_CALL
 *  ebx = FILE_DESCRIPTOR
 *  ecx = VARIABLE
 *  edx = LEN_OF_VARIABLE
 *  
 * */


void write_constants(FILE* file);
void call_kernel(FILE* file);
void select_call(FILE* file, Call sys_call);
void select_file_descriptor(FILE* file, FileDescriptor fd );
void select_variable(FILE* file, char* variable_name, int size);

#endif
