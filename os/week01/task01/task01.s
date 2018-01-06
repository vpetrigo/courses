.att_syntax
.section .text
.globl main
main:
	movq $1, %rdx
	movq $2, %rsi
	xchgq %rsi, %rdx
