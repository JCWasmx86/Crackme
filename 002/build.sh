#!/usr/bin/env bash
nasm shell.asm || exit
gcc -fanalyzer -O3 -Wall -o encrypt helper.s encrypt.c || exit
./encrypt shell shell.encrypted || exit
echo "__attribute__((aligned(16384)))" > data.h
xxd -i shell.encrypted | head -n 30 | sed s/shell_encrypted/data/g >> data.h
gcc -fanalyzer -O3 -Wall -s -o cm002 main.c helper.s -fno-ident -fno-exceptions -fno-asynchronous-unwind-tables|| exit
rm data.h shell shell.encrypted
strip -s -v cm002
