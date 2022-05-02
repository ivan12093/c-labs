#!/bin/bash

# $1 - first file
# $2 - second file

res=$(cmp "$1" "$2")

if [ "$res" == "" ]; then
    exit 0
else
    exit 1
fi          
