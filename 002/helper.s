.global rdtsc
.global swap_halves_of_byte
.global ror
.global rol
rdtsc:
	rdtsc
	shl $8, %rdx
	or %rdx, %rax
	ret
swap_halves_of_byte:
	and $0xff, %rdi
	mov %rdi, %rsi
	and $0x0f, %rsi
	shr $4, %rdi
	and $0x0f, %rdi
	shl $4, %rsi
	or %rsi, %rdi
	mov %rdi, %rax
	ret
ror:
	and $0xff, %rdi
	mov %rsi, %rcx
	ror %cl, %rdi
	mov %rdi, %rax
	ret
rol:
	and $0xff, %rdi
	mov %rsi, %rcx
	rol %cl, %rdi
	mov %rdi, %rax
	ret
