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
# Print current instruction
(gdb) n
# Print registers info
(gdb) info r
```
