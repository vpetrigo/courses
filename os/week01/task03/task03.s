.att_syntax
.section .text
.globl main

main:
    xor %rsi, %rsi
    xor %rax, %rax
    xor %rdx, %rdx
    mov $40, %sil
    call fahr_to_cels
.inf1:
    jmp .inf1

.set fahr_mul, 5
.set fahr_div, 9
.set fahr_sub, 32

fahr_to_cels:
    sub $fahr_sub, %rsi
    mov $fahr_mul, %rax
    mulq %rsi
    mov $fahr_div, %rsi
    divq %rsi
    mov %rax, %rsi
    ret 
