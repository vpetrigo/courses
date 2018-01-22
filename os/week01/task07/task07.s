.att_syntax
.section .text
.global main

.extern printf

hello:
    .asciz "Pow %d\n"

main:
    movq $2, %rdi
    movq $4, %rsi
    call pow
    pushq %rbp
    leaq (%rsp), %rbp
    subq $32, %rsp
	leaq hello, %rcx
    movq %rax, %rdx
	callq printf
    addq $32, %rsp
    popq %rbp
    retq

pow:
    movq $1, %rax
pow_op:
    subq $1, %rsi
    jl pow_exit
    mulq %rdi
    jmp pow_op
pow_exit:
    ret
