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

echo -e "${CYAN}EXECUTING POSITIVE TESTS${NORMAL}"

while [ -f "${next_pattern}_in.txt" ]; do

	if [ -f "${next_pattern}_args.txt" ]; then
		./pos_case.sh "${next_pattern}_in.txt" "${next_pattern}_out.txt" "${next_pattern}_args.txt"
    else
        ./pos_case.sh "${next_pattern}_in.txt" "${next_pattern}_out.txt"
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
done

echo -e "${CYAN}EXECUTING NEGATIVE TESTS${NORMAL}"

counter=1
update_counter "$counter"
next_pattern="../data/neg_${test_number}"

while [ -f "${next_pattern}_in.txt" ]; do

    if [ -f "${next_pattern}_args.txt" ]; then
        ./neg_case.sh "${next_pattern}_in.txt" "${next_pattern}_args.txt"
    else
        ./neg_case.sh "${next_pattern}_in.txt"
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

done

rm test_out.txt
exit $failed_tests
