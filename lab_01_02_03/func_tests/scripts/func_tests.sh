#!/bin/bash

function update_next_pattern() {
    # $1 - current counter
    # $2 - pos or neg
    if [ "$1" -lt 10 ]; then
        next_pattern="${tests_dir}${2}_0${counter}"
    else
        next_pattern="${tests_dir}${2}_${counter}"
    fi
}

RED='\e[91m'
GREEN='\e[92m'
CYAN='\e[96m'
NORMAL='\e[39m'

failed_tests=0

tests_dir="../data/"
counter=1

update_next_pattern $counter pos


echo -e "${CYAN}EXECUTING POSITIVE TESTS${NORMAL}"

while [ -f "${next_pattern}_in.txt" ]; do

	if [ -f "${next_pattern}_args.txt" ]; then
		./pos_case.sh "${next_pattern}_in.txt" "${next_pattern}_out.txt" "${next_pattern}_args.txt"
    else
        ./pos_case.sh "${next_pattern}_in.txt" "${next_pattern}_out.txt"
    fi

    if [ $? -eq 0 ]; then
        echo -e "[TEST #${counter}] ${GREEN}PASSED${NORMAL}"
    else
        echo -e "[TEST ${counter}] ${RED}FAILED${NORMAL}"
        failed_tests=$((failed_tests+1))
    fi

    counter=$((counter+1))
    update_next_pattern $counter pos
done

echo -e "${CYAN}EXECUTING NEGATIVE TESTS${NORMAL}"

counter=1
update_next_pattern $counter neg
while [ -f "${next_pattern}_in.txt" ]; do

    if [ -f "${next_pattern}_args.txt" ]; then
        ./neg_case.sh "${next_pattern}_in.txt" "${next_pattern}_args.txt"
    else
        ./neg_case.sh "${next_pattern}_in.txt"
    fi

    if [ $? -eq 0 ]; then
        echo -e "[TEST #${counter}] ${GREEN}PASSED${NORMAL}"
    else
        echo -e "[TEST #${counter}] ${RED}FAILED${NORMAL}"
        failed_tests=$((failed_tests+1))
    fi

    counter=$((counter+1))
    update_next_pattern $counter neg
done

rm test_out.txt
exit $failed_tests
