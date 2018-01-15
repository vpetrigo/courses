.att_syntax
.section .text
.global main

main:
    xor %rsi, %rsi
    xor %rdx, %rdx
    mov $12, %sil
    mov $64, %dl
    call swap_val
.inf1:
    jmp .inf1

swap_val:
    pushq %rdx
    movq %rsi, %rdx
    popq %rsi
    ret
