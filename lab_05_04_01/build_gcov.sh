#!/bin/bash

gcc -c main.c student.c struct_file.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -O0 --coverage
gcc -o app.exe main.o student.o struct_file.o --coverage -lm

