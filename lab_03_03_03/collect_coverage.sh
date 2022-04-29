#!/bin/bash

#RETURN CODE
# 1 - dir func_tests/scripts doesn`t exists

cd func_tests/scripts/ || exit 1
./func_tests.sh
cd ../../

gcov -r main.c
