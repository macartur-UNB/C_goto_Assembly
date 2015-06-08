section .bss
	nome resb 1 
	data resd 1 
section .data
	hair db 'H' 
	sex db 'M' 
	teste dd 1 
	precision dd 1 
section .text
	global _start

_start:
	push ebp
	mov ebp, esp
	sub esp, 1024
	mov [esp + 8], word 48
	mov ax, WORD [esp + 8]
	push word ax

	mov eax, 3
	push word ax

	xor eax, eax
	xor ebx, ebx
	pop WORD ax
	pop WORD bx
	add eax, ebx
	push eax

	mov eax, 2
	push word ax

	xor eax, eax
	xor ebx, ebx
	pop WORD ax
	pop WORD bx
	sub eax, ebx
	push word ax
	
	mov eax, 4
	mov ebx, 1
	mov ecx, esp
	mov edx, 2
	int 0x80

	mov esp, ebp
	pop ebp

exit:
	mov eax, 1
	xor ebx, ebx
	int 0x80

add:
	push ebp
	mov ebp, esp
	sub esp, 1024
	mov esp, ebp
	pop ebp
	ret
