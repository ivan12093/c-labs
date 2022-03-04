#!/bin/bash

function update_counter() {
    # $1 - current counter
    if [ "$1" -lt 10 ]; then
        test_number="0${counter}"
    else
        test_number="${counter}"
    fi
}

RED='\e[91m'
GREEN='\e[92m'
CYAN='\e[96m'
NORMAL='\e[39m'

failed_tests=0

counter=1
update_counter "$counter"
next_pattern="../data/pos_${test_number}"
sec_next_pattern="../data/pos_${counter}"

echo -e "${CYAN}EXECUTING POSITIVE TESTS${NORMAL}"

while [ -f "${next_pattern}_in.txt" -o -f "${sec_next_pattern}_in.txt" ]; do

    cur_pattern="${next_pattern}"
    if [ ! -f "${cur_pattern}_in.txt" ]; then
        cur_pattern="$sec_next_pattern"
    fi

	if [ -f "${cur_pattern}_args.txt" ]; then
		./pos_case.sh "${cur_pattern}_in.txt" "${cur_pattern}_out.txt" "${cur_pattern}_args.txt"
    else
        ./pos_case.sh "${cur_pattern}_in.txt" "${cur_pattern}_out.txt"
    fi
	
	return_code=$?
    if [ "$return_code" -eq 0 ]; then
        echo -e "[TEST #${test_number}] ${GREEN}PASSED${NORMAL}"
    else
        echo -e "[TEST #${test_number}] ${RED}FAILED${NORMAL}"
        failed_tests=$((failed_tests+1))
    fi

    counter=$((counter+1))
    update_counter $counter
	next_pattern="../data/pos_${test_number}"
    sec_next_pattern="../data/pos_${counter}"

done

echo -e "${CYAN}EXECUTING NEGATIVE TESTS${NORMAL}"

counter=1
update_counter "$counter"
next_pattern="../data/neg_${test_number}"
sec_next_pattern="../data/neg_${counter}"

while [ -f "${next_pattern}_in.txt" -o -f "${sec_next_pattern}_in.txt" ]; do

    cur_pattern="${next_pattern}"
    if [ ! -f "${cur_pattern}_in.txt" ]; then
        cur_pattern="$sec_next_pattern"
    fi

    if [ -f "${next_pattern}_args.txt" ]; then
        ./neg_case.sh "${cur_pattern}_in.txt" "${cur_pattern}_args.txt"
    else
        ./neg_case.sh "${cur_pattern}_in.txt"
    fi

	return_code=$?
    if [ "$return_code" -eq 0 ]; then
        echo -e "[TEST #${test_number}] ${GREEN}PASSED${NORMAL}"
    else
        echo -e "[TEST #${test_number}] ${RED}FAILED${NORMAL}"
        failed_tests=$((failed_tests+1))
    fi

    counter=$((counter+1))
    update_counter $counter 
    next_pattern="../data/neg_${test_number}"
    sec_next_pattern="../data/neg_${counter}"

done

rm test_out.txt
exit $failed_tests
