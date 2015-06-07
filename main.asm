section .bss
	nome resb 1 
	data resd 1 
section .data
	hair db 'H' 
	sex db 'M' 
	test dd 1 
	precision dd 1 
section .text
	global _start

_start:
	push ebp
	mov ebp, esp
	sub esp, 1024
	mov ax, WORD [esp + 10]
	xor eax, eax
	push word ax

	mov eax, 3
	push word ax

	mov eax, 2.3
	push eax

	mov esp, ebp
	pop ebp
add:
	push ebp
	mov ebp, esp
	sub esp, 1024
	mov esp, ebp
	pop ebp
