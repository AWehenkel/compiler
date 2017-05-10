	.file	"m_err.c"
	.text
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
# BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, %eax
	movl	$0, -4(%ebp)
	movl	$1, -8(%ebp)
	movl	$2, -12(%ebp)
	movl	-8(%ebp), %ecx
	addl	-12(%ebp), %ecx
	movl	%ecx, -16(%ebp)
	addl	$16, %esp
	popl	%ebp
	ret
.Ltmp0:
	.size	main, .Ltmp0-main


	.ident	"Ubuntu clang version 3.4-1ubuntu3 (tags/RELEASE_34/final) (based on LLVM 3.4)"
	.section	".note.GNU-stack","",@progbits
