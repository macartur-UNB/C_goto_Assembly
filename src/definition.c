#include "definition.h"
#include <string.h>

int n_constants =7;
char* constants[] = {  "SYS_EXIT\tequ 1",
                       "SYS_WRITE\tequ 4",
                       "SYS_READ\tequ 3",
                       "STDIN\tequ 0",
                       "STDOUT\tequ 1",
					   "STDERR\tequ 2",
                       "KERNEL\tequ 80h"
                    };

void 
write_constants(FILE* file)
{
	int i;
    for (i=0;i < n_constants;i++)
        fprintf(file,"%s\n",constants[i]);
	fprintf(file,"\n");
}

void
select_call(FILE* file, Call sys_call)
{
	char call[25]="";

	switch(sys_call)
	{
		case SYS_EXIT:  strcat(call,"SYS_EXIT"); break;
		case SYS_FORK:  strcat(call,"SYS_FORK"); break;
		case SYS_READ:  strcat(call,"SYS_READ"); break;
		case SYS_WRITE: strcat(call,"SYS_WRITE"); break;
		case SYS_OPEN:  strcat(call,"SYS_OPEN"); break;
		case SYS_CLOSE: strcat(call,"SYS_CLOSE"); break;
	}
	fprintf(file,"mov eax, %s\n",call);
}

void
select_file_descriptor(FILE* file, FileDescriptor fd )
{
	char selected[20]="";
	switch(fd)
	{
		case STDIN:  strcat(selected,"STDIN");break;
		case STDOUT: strcat(selected,"STDOUT");break;
		case STDERR: strcat(selected,"STDERR");break;
	}
	fprintf(file,"mov ebx, %s\n",selected);
}

void 
call_kernel(FILE* file)
{
	fprintf(file,"int KERNEL\n");
}

void
select_variable( FILE* file,char* variable_name, int size)
{
	fprintf(file,"mov ecx, %s\n",variable_name);
	fprintf(file,"mov edx, %i\n",size);
}

