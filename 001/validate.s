.global validate
.global validation_failed

validate:
	cmp $64, %esi
	mov %rdi, pwd
	jne validation_failed
	movupd (%rdi), %xmm0
	movupd 16(%rdi), %xmm1
	movupd 32(%rdi), %xmm2
	movupd 48(%rdi), %xmm3
	pxor xor, %xmm0
	# "aB13wvno=(102-{?" is the first part, without the quotes
	xor %eax, %eax
	pextrb $0, %xmm0, %r8d
	xor %r8d, %eax
	pextrb $1, %xmm0, %r8d
	xor %r8d, %eax
	pextrb $2, %xmm0, %r8d
	xor %r8d, %eax
	pextrb $3, %xmm0, %r8d
	xor %r8d, %eax
	pextrb $4, %xmm0, %r8d
	xor %r8d, %eax
	pextrb $5, %xmm0, %r8d
	xor %r8d, %eax
	pextrb $6, %xmm0, %r8d
	xor %r8d, %eax
	pextrb $7, %xmm0, %r8d
	xor %r8d, %eax
	pextrb $8, %xmm0, %r8d
	xor %r8d, %eax
	pextrb $9, %xmm0, %r8d
	xor %r8d, %eax
	pextrb $10, %xmm0, %r8d
	xor %r8d, %eax
	pextrb $11, %xmm0, %r8d
	xor %r8d, %eax
	pextrb $12, %xmm0, %r8d
	xor %r8d, %eax
	pextrb $13, %xmm0, %r8d
	xor %r8d, %eax
	pextrb $14, %xmm0, %r8d
	xor %r8d, %eax
	pextrb $15, %xmm0, %r8d
	xor %r8d, %eax
	cmp $0, %eax
	jne validation_failed
	# "03RE$%"V1T-<s3GL" as second part, without the outer quotes
	mov $17, %rax
	add %rax, %rax # 34
	xor %r8, %r8
	pextrb $11, %xmm0, %r8d
	imul %r8, %rax # 170
	add %rax, %rax # 340
	add %rax, %rax # 680
	add $314, %rax # 994
	movupd %xmm1, (tmp)
	xor %rcx, %rcx
	mov $tmp, %r8
	xor %rbx, %rbx
.loop:
	movb 0(%r8, %rcx, 1), %bl
	sub %rbx , %rax
	inc %rcx
	cmp $16, %ecx
	jne .loop
	cmp $0, %rax
	jne validation_failed
	movq %xmm3, %rax
	pextrq $1, %xmm2, %rbx
	xor %rbx, %rax
	mov $0xFFFF231203, %rbx
	pextrq $1, %xmm3, %r8
	movq %xmm2, %r9
	mov %r9, (tmp)
	mov %r8, (tmp2)
	div %rbx, %rax
	// Flag is aB13wvno=(102-{?03RE$%"V1T-<s3GL12345678AAAAAAAAAAAAAAAA87654321
validation_failed:
	mov $1, %rax
	mov $1, %rdi
	mov $msg, %rsi
	mov $28, %rdx
	syscall
	mov $60, %rax
	mov $1, %rdi
	syscall
.data
msg:
	.asciz "Failed to validate password\n"
.align 16
xor:
.byte 100
.byte 71
.byte 52
.byte 54
.byte 114
.byte 115
.byte 107
.byte 106
.byte 56
.byte 45
.byte 52
.byte 53
.byte 55
.byte 40
.byte 126
.byte 58
.align 16
.comm tmp, 8
.comm tmp2, 8
.comm pwd, 8
