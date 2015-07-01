extern printf
extern scanf
section .bss
	nome resb 1 
	data resd 1 
section .data
	hair db 'H' 
	sex db 'M' 
	teste: dd 1 
	precision: dd 1 
section .text
	global main

main:
	push ebp
	mov ebp, esp
	push DWORD 2
	push DWORD 3
	pop ebx
	pop eax
	add eax, ebx
	push DWORD eax
	pop WORD ax
	mov WORD [esp + 4], ax
	mov esp, ebp
	pop ebp
