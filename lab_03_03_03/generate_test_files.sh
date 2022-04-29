#!/bin/bash

### RETURN CODES 

# 0 - SUCCESS.
# 1 - DIR func_tests/scripts/ DOESN`T EXISTS.

### ARGS

# $1 - count of positive tests.
# $2 - count of negative tests.

function get_test_number() {
    # $1 - current counter
    if [ "$1" -lt 10 ]; then
        test_number="0${counter}"
    else
        test_number="${counter}"
    fi
}

cd func_tests/scripts/ || exit 1

pos="$1"
neg="$2"

counter=1
get_test_number "$counter"
next_pattern="../data/pos_${test_number}"

while [ $counter -le "$pos" ]; do
    touch "${next_pattern}_in.txt"
    touch "${next_pattern}_out.txt"
    counter=$((counter+1))
    get_test_number "$counter"
    next_pattern="../data/pos_${test_number}"
done

counter=1
get_test_number "$counter"
next_pattern="../data/neg_${test_number}"

while [ $counter -le "$neg" ]; do
    touch "${next_pattern}_in.txt"
    counter=$((counter+1))
    get_test_number "$counter"
    next_pattern="../data/neg_${test_number}"
done

cd ../../