.att_syntax

.section .data

value1:
    .quad 1024

value2:
    .quad 64

.section .text
.global main

main:
    xor %rdi, %rdi
    xor %rsi, %rsi
    movq $value1, %rsi
    movq $value2, %rdi
    call swap
.inf1:
    jmp .inf1

swap:
    pushq (%rdi)
    pushq (%rsi)
    popq (%rdi)
    popq (%rsi)
    ret
