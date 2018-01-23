# Run ASM solutions

Compile an example with `gcc`/`clang`:

```bash
$ gcc -g task01.s -o task01
```

Run GDB on a resulting executable file

```bash

$ gdb task01

(gdb) b main
(gdb) r
# Print current file listing
(gdb) list
# Next instruction
(gdb) n
# Print registers info
(gdb) info r
```

# Calling convention (MinGW)

Caller is responsible for allocating space on the stack for callee to
be able to save content of `rcx, rdx, r8, r9` on the stack

```asm
; store stack frame
pushq %rbp
leaq (%rsp), %rbp
; allocate stack for storing 4 8-byte registers
subq $32, %rsp
; set up paramters
leaq hello, %rcx
movq %rax, %rdx
; call printf
callq printf
; restore stack
addq $32, %rsp
; restore frame
popq %rbp
```