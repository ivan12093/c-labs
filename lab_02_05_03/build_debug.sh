#!/bin/bash

gcc -c main.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -O0 -ggdb
gcc -o app.exe main.o
