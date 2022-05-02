#!/bin/bash

# $1 - first file
# $2 - second file

diff "$1" "$2" > /dev/null 2>&1
res=$?

if [ $res ]; then
    exit 0
else
    exit 1
fi          
