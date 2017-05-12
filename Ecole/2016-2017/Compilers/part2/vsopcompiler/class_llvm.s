	.text
	.file	"class_llvm.ll"
	.globl	Parent_init
	.align	16, 0x90
	.type	Parent_init,@function
Parent_init:                            # @Parent_init
# BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%eax
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
	addl	$4, %esp
	popl	%ebp
	retl
.Lfunc_end0:
	.size	Parent_init, .Lfunc_end0-Parent_init

	.globl	Parent_inheritedMethod
	.align	16, 0x90
	.type	Parent_inheritedMethod,@function
Parent_inheritedMethod:                 # @Parent_inheritedMethod
# BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%eax
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
	addl	$4, %esp
	popl	%ebp
	retl
.Lfunc_end1:
	.size	Parent_inheritedMethod, .Lfunc_end1-Parent_inheritedMethod

	.globl	Child_overriddenMethod
	.align	16, 0x90
	.type	Child_overriddenMethod,@function
Child_overriddenMethod:                 # @Child_overriddenMethod
# BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%eax
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
	addl	$4, %esp
	popl	%ebp
	retl
.Lfunc_end2:
	.size	Child_overriddenMethod, .Lfunc_end2-Child_overriddenMethod

	.globl	Child_newMethod
	.align	16, 0x90
	.type	Child_newMethod,@function
Child_newMethod:                        # @Child_newMethod
# BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %ecx
	movl	%ecx, -4(%ebp)
	movl	%eax, -8(%ebp)
	addl	$8, %esp
	popl	%ebp
	retl
.Lfunc_end3:
	.size	Child_newMethod, .Lfunc_end3-Child_newMethod

	.globl	Child_init
	.align	16, 0x90
	.type	Child_init,@function
Child_init:                             # @Child_init
# BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	%eax, (%esp)
	calll	Parent_init
	movl	-4(%ebp), %eax
	movl	$0, 8(%eax)
	movl	-4(%ebp), %eax
	movl	$ChildVTable_inst, (%eax)
	movb	$99, -19(%ebp)
	addl	$40, %esp
	popl	%ebp
	retl
.Lfunc_end4:
	.size	Child_init, .Lfunc_end4-Child_init

	.globl	Child_new
	.align	16, 0x90
	.type	Child_new,@function
Child_new:                              # @Child_new
# BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$1, -4(%ebp)
	movl	$16, (%esp)
	calll	malloc
	movl	%eax, -8(%ebp)
	testl	%eax, %eax
	je	.LBB5_2
# BB#1:
	movl	-8(%ebp), %eax
	movl	%eax, (%esp)
	calll	Child_init
	movl	-8(%ebp), %eax
	addl	$24, %esp
	popl	%ebp
	retl
.LBB5_2:
	movl	$.L__PRETTY_FUNCTION__.Child_new, 12(%esp)
	movl	$52, 8(%esp)
	movl	$.L.str.1, 4(%esp)
	movl	$.L.str, (%esp)
	calll	__assert_fail
.Lfunc_end5:
	.size	Child_new, .Lfunc_end5-Child_new

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
# BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	calll	Child_new
	movl	%eax, -4(%ebp)
	movl	(%eax), %ecx
	movl	%eax, (%esp)
	movl	$42, 4(%esp)
	calll	*8(%ecx)
	xorl	%eax, %eax
	addl	$24, %esp
	popl	%ebp
	retl
.Lfunc_end6:
	.size	main, .Lfunc_end6-main

	.type	ChildVTable_inst,@object # @ChildVTable_inst
	.data
	.globl	ChildVTable_inst
	.align	4
ChildVTable_inst:
	.long	Parent_inheritedMethod
	.long	Child_overriddenMethod
	.long	Child_newMethod
	.size	ChildVTable_inst, 12

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"self"
	.size	.L.str, 5

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"class_llvm.c"
	.size	.L.str.1, 13

	.type	.L__PRETTY_FUNCTION__.Child_new,@object # @__PRETTY_FUNCTION__.Child_new
.L__PRETTY_FUNCTION__.Child_new:
	.asciz	"struct Child *Child_new()"
	.size	.L__PRETTY_FUNCTION__.Child_new, 26


	.ident	"clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)"
	.section	".note.GNU-stack","",@progbits
