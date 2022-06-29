#!/bin/bash
set -e -x
yacc -d *.y
lex *.l
gcc -fsanitize=address -g lex.yy.c y.tab.c -ll
./a.out

