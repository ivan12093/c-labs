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

input_file="../data/${1}"

if [ ! -f "$input_file" ]; then
    exit 1
fi

keys=""

if [ $# -gt 1 ]; then
    keys_file="../data/${3}"
    if [ ! -f "$keys_file" ];then
        exit 2
    fi
    keys=$(cat "$keys_file")
fi

if [ -n "${USE_VALGRIND}" ]; then
    valgrind ../../app.exe "$keys" < "$input_file" > "test_out.txt"
else
    ../../app.exe "$keys" < "$input_file" > "test_out.txt"
fi

return_code=$?
if [ "$return_code" -ne 0 ] && [ "$return_code" -ne 100 ]; then
    exit 0
fi

exit 1
~                           
