#!/bin/bash

### RETURN CODES:
# 0 - SUCCESS
# 1 - ONE OF THE OBILGATORY ARGS DOESN`T EXISTS
# 2 - OPTIONAL ARG WAS DECLARED BUT DOESN`T EXISTS
# 3 - THE PROGRAM UNDER TEST RETURNED AN ERROR
# 4 - ALL REQUIRED PARAMETS WEREN`T ENTERED
# 5 - COMPAROR RETURNED FAILURE

### ARGUMENTS
# $1 - input file
# $2 - output file
# $3 - keys_file (optional)

if [ $# -lt 2 ]; then
    exit 4
fi

input_file="../data/${1}"
output_file="../data/${2}"

if [[ ! ( -f "$input_file" && -f "$output_file" ) ]]; then
    exit 1
fi

keys=""

if [ $# -gt 2 ]; then
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
    exit 3
fi

./comparator.sh "$output_file" "test_out.txt"

return_code=$?
if [ "$return_code" -eq 0 ]; then
    exit 0
else
    exit 5
fi
~         
