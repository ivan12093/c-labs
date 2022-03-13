#!/bin/bash

### RETURN CODES:
# 0 - SUCCESS
# 1 - ONE OF THE OBILGATORY ARGS DOESN`T EXISTS
# 2 - OPTIONAL ARG WAS DECLARED BUT DOESN`T EXISTS
# 3 - THE PROGRAM UNDER TEST RETURNED AN ERROR
# 4 - ALL REQUIRED PARAMETS WEREN`T ENTERED

### ARGUMENTS
# $1 - input file
# $2 - keys_file (optional)

if [ $# -lt 1 ]; then
    exit 4
fi

input_file="${1}"

if [ ! -f "$input_file" ]; then
    exit 1
fi

keys=""

if [ $# -gt 1 ]; then
    keys_file="${2}"
    if [ ! -f "$keys_file" ];then
        exit 2
    fi
    keys=$(cat "$keys_file")
fi
USE_VALGRIND="YES"
if [ -n "${USE_VALGRIND}" ]; then
    eval "valgrind --log-file=../../valgrind_$(date +%N).log ../../app.exe '$keys' < ${input_file} > test_out.txt"
else
    eval "../../app.exe '$keys' < ${input_file} > test_out.txt"
fi

return_code=$?
if [ "$return_code" -ne 0 ]; then
    exit 0
fi

exit 1
~                           
