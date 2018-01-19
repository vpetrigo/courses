.att_syntax
.section .text
.global main

main:
    xor %rdi, %rdi
    xor %rsi, %rsi
    movq $10, %rdi
    movq $4, %rsi
    call min
.inf1:
    jmp .inf1

min:
    movq %rdi, %rax
    cmpq %rdi, %rsi
    ja min_exit
    movq %rsi, %rax
min_exit:
    ret
