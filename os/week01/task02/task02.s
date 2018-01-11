.att_syntax
.section .text
.globl main

main:
    movq $100, %rdx
    movq $200, %rsi
    addq %rdx, %rsi
.inf1:
    jmp .inf1
