bits 64
section .text
input_string: resb 256
; 'CDHJM"DDA ', without outer quotes
_start:
	lea r8, [rel input_string]
	cmp byte [r8 + 4], 'M'
	jne not_valid
	; RDI is pointer to function, if fail
	; RSI is pointer to function, if success
	; RCX is length of string
	cmp byte [r8 + 9], ' '
	jne not_valid
	cmp byte [r8 + 5], '"'
	jne not_valid
	cmp byte [r8 + 8], '/'
	je not_valid
	cmp dword [r8], 0x4344484a ; CDHJ
	cmp word [r8 + 6], 0x4444; DD
	jmp rsi
not_valid:
	jmp rdi
addr:
	pop rax
	push rax
	ret
align 4
bar: dd 3402
