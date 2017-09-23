#!/bin/bash

gcc -DCORRECT pre-proc1.c
gcc linker.c -lm
gcc -c -fpic lib/mul.c -o lib/mul.o
gcc -shared lib/mul.o -o lib/libmul.so
gcc -c linker2.c -I./include
gcc linker2.o -L./lib -lmul
gcc -c linker3.c
gcc -c foo.c
gcc foo.o linker3.o -L./lib -lmul
objdump -Dr linker3.o > linker3.o.asm
objdump -Dr a.out > a.out.asm
