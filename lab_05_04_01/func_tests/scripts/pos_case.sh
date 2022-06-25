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

input_file="${1}"
output_file="${2}"

if [[ ! ( -f "$input_file" && -f "$output_file" ) ]]; then
    exit 1
fi

keys=""

if [ $# -gt 2 ]; then
    keys_file="${3}"
    if [ ! -f "$keys_file" ];then
        exit 2
    fi
	read -ra keys <<< "$(cat "$keys_file")"
fi

if [[ "${keys[0]}" == "sb" ]]; then
    touch "content_copy.txt"
    cat "../data/${keys[1]}" > "content_copy.txt"
    if [ -n "${USE_VALGRIND}" ]; then
        eval "valgrind --log-file=../../valgrind_$(date +%N).log ../../app.exe ${keys[0]} content_copy.txt < ${input_file} > test_out.txt"
    else
        eval "../../app.exe ${keys[0]} content_copy.txt < ${input_file} > test_out.txt"
    fi
    rm "content_copy.txt"
    return_code=$?
    if [ "$return_code" -ne 0 ]; then
        exit 3
    fi

    ./comparator.sh "$output_file" "test_out.txt"

    return_code=$?
    if [ "$return_code" -eq 0 ]; then
        exit 0
    else
        exit 5
    fi
elif [[ "${keys[0]}" == "db" ]]; then
    touch "test_out.txt"
    cat "../data/${keys[1]}" > "test_out.txt"
    if [ -n "${USE_VALGRIND}" ]; then
        eval "valgrind --log-file=../../valgrind_$(date +%N).log ../../app.exe ${keys[0]} test_out.txt"
    else
        eval "../../app.exe ${keys[0]} test_out.txt"
    fi

    return_code=$?
    if [ "$return_code" -ne 0 ]; then
        exit 3
    fi

    ./comparator.sh "$output_file" "test_out.txt"

    return_code=$?
    if [ "$return_code" -eq 0 ]; then
        exit 0
    else
        exit 5
    fi
elif [[ "${keys[0]}" == "fb" ]]; then
    touch "test_out.txt"
    if [ -n "${USE_VALGRIND}" ]; then
        eval "valgrind --log-file=../../valgrind_$(date +%N).log ../../app.exe ${keys[0]} ${keys[1]} test_out.txt ${keys[3]}"
    else
        eval "../../app.exe ${keys[0]} ${keys[1]} test_out.txt ${keys[3]}"
    fi

    return_code=$?
    if [ "$return_code" -ne 0 ]; then
        exit 3
    fi

    ./comparator.sh "$output_file" "test_out.txt"

    return_code=$?
    if [ "$return_code" -eq 0 ]; then
        exit 0
    else
        exit 5
    fi
fi
