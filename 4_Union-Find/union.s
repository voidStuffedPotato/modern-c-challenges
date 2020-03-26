	.file	"union.c"
	.text
	.p2align 4
	.globl	MakeSingleton
	.type	MakeSingleton, @function
MakeSingleton:
.LFB23:
	.cfi_startproc
	testq	%rsi, %rsi
	je	.L1
	leaq	0(,%rsi,8), %rdx
	movl	$255, %esi
	jmp	memset@PLT
	.p2align 4,,10
	.p2align 3
.L1:
	ret
	.cfi_endproc
.LFE23:
	.size	MakeSingleton, .-MakeSingleton
	.p2align 4
	.globl	Find
	.type	Find, @function
Find:
.LFB24:
	.cfi_startproc
	.p2align 4,,10
	.p2align 3
.L5:
	movq	%rsi, %rax
	movq	(%rdi,%rsi,8), %rsi
	cmpq	$-1, %rsi
	jne	.L5
	ret
	.cfi_endproc
.LFE24:
	.size	Find, .-Find
	.p2align 4
	.globl	FindReplace
	.type	FindReplace, @function
FindReplace:
.LFB25:
	.cfi_startproc
	leaq	(%rdi,%rsi,8), %rcx
	movq	(%rcx), %rax
	cmpq	$-1, %rax
	je	.L8
	.p2align 4,,10
	.p2align 3
.L9:
	movq	%rdx, (%rcx)
	leaq	(%rdi,%rax,8), %rcx
	movq	%rax, %rsi
	movq	(%rcx), %rax
	cmpq	$-1, %rax
	jne	.L9
.L8:
	cmpq	%rsi, %rdx
	je	.L7
	movq	%rdx, (%rcx)
.L7:
	ret
	.cfi_endproc
.LFE25:
	.size	FindReplace, .-FindReplace
	.p2align 4
	.globl	FindCompress
	.type	FindCompress, @function
FindCompress:
.LFB26:
	.cfi_startproc
	movq	%rsi, %rax
	.p2align 4,,10
	.p2align 3
.L16:
	movq	%rax, %r8
	movq	(%rdi,%rax,8), %rax
	cmpq	$-1, %rax
	jne	.L16
	leaq	(%rdi,%rsi,8), %rdx
	movq	(%rdx), %rax
	cmpq	$-1, %rax
	je	.L15
	.p2align 4,,10
	.p2align 3
.L18:
	movq	%r8, (%rdx)
	leaq	(%rdi,%rax,8), %rdx
	movq	(%rdx), %rax
	cmpq	$-1, %rax
	jne	.L18
.L15:
	movq	%r8, %rax
	ret
	.cfi_endproc
.LFE26:
	.size	FindCompress, .-FindCompress
	.p2align 4
	.globl	Union
	.type	Union, @function
Union:
.LFB27:
	.cfi_startproc
	movq	%rsi, %rax
	.p2align 4,,10
	.p2align 3
.L25:
	movq	%rax, %r8
	movq	(%rdi,%rax,8), %rax
	cmpq	$-1, %rax
	jne	.L25
	leaq	(%rdi,%rsi,8), %rcx
	movq	(%rcx), %rax
	cmpq	$-1, %rax
	je	.L26
	.p2align 4,,10
	.p2align 3
.L27:
	movq	%r8, (%rcx)
	leaq	(%rdi,%rax,8), %rcx
	movq	(%rcx), %rax
	cmpq	$-1, %rax
	jne	.L27
.L26:
	leaq	(%rdi,%rdx,8), %rcx
	movq	(%rcx), %rax
	cmpq	$-1, %rax
	je	.L28
	.p2align 4,,10
	.p2align 3
.L29:
	movq	%r8, (%rcx)
	leaq	(%rdi,%rax,8), %rcx
	movq	%rax, %rdx
	movq	(%rcx), %rax
	cmpq	$-1, %rax
	jne	.L29
.L28:
	cmpq	%rdx, %r8
	je	.L24
	movq	%r8, (%rcx)
.L24:
	movq	%r8, %rax
	ret
	.cfi_endproc
.LFE27:
	.size	Union, .-Union
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%zu -> %zu root = %zu\n"
	.text
	.p2align 4
	.globl	Show
	.type	Show, @function
Show:
.LFB28:
	.cfi_startproc
	cmpq	$1, %rsi
	jbe	.L47
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	leaq	.LC0(%rip), %r13
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rsi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movl	$1, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	.p2align 4,,10
	.p2align 3
.L43:
	movq	%rbp, %rax
	.p2align 4,,10
	.p2align 3
.L42:
	movq	%rax, %rcx
	movq	(%rbx,%rax,8), %rax
	cmpq	$-1, %rax
	jne	.L42
	movq	(%rbx,%rbp,8), %rdx
	movq	%rbp, %rsi
	movq	%r13, %rdi
	xorl	%eax, %eax
	addq	$1, %rbp
	call	printf@PLT
	cmpq	%rbp, %r12
	jne	.L43
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L47:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	ret
	.cfi_endproc
.LFE28:
	.size	Show, .-Show
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pcmpeqd	%xmm0, %xmm0
	movl	$10, %esi
	subq	$96, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 88(%rsp)
	xorl	%eax, %eax
	movaps	%xmm0, (%rsp)
	movdqa	.LC1(%rip), %xmm0
	movq	%rsp, %rbp
	movq	$8, 72(%rsp)
	movq	%rbp, %rdi
	movups	%xmm0, 8(%rsp)
	movdqa	.LC2(%rip), %xmm0
	movups	%xmm0, 24(%rsp)
	movdqa	.LC3(%rip), %xmm0
	movups	%xmm0, 40(%rsp)
	movdqa	.LC4(%rip), %xmm0
	movups	%xmm0, 56(%rsp)
	call	Show
	movq	72(%rsp), %rax
	leaq	72(%rsp), %rdx
	cmpq	$-1, %rax
	je	.L51
	.p2align 4,,10
	.p2align 3
.L52:
	movq	$0, (%rdx)
	leaq	0(%rbp,%rax,8), %rdx
	movq	%rax, %rcx
	movq	(%rdx), %rax
	cmpq	$-1, %rax
	jne	.L52
	testq	%rcx, %rcx
	je	.L53
.L51:
	movq	$0, (%rdx)
.L53:
	movl	$10, %esi
	movq	%rbp, %rdi
	call	Show
	movq	88(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L61
	addq	$96, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	xorl	%eax, %eax
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L61:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE22:
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC1:
	.quad	0
	.quad	1
	.align 16
.LC2:
	.quad	2
	.quad	3
	.align 16
.LC3:
	.quad	4
	.quad	5
	.align 16
.LC4:
	.quad	6
	.quad	7
	.ident	"GCC: (Arch Linux 9.2.1+20200130-2) 9.2.1 20200130"
	.section	.note.GNU-stack,"",@progbits
