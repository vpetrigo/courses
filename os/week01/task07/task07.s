.att_syntax
.section .text
.global main

main:
    xor %rdi, %rdi
    xor %rsi, %rsi
    movq $8, %rdi
    movq $3, %rsi
    call pow
.inf1:
    jmp .inf1

pow:
    movq $1, %rax
pow_op:
    subq $1, %rsi
    jl pow_exit
    mulq %rdi
    jmp pow_op
pow_exit:
    ret
