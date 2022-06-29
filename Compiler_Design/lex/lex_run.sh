#!/bin/bash
set -e
set -x
lex *.l
gcc lex.yy.c -ll
./a.out $@

