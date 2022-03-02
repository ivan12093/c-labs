#!/bin/bash

# $1 - first file
# $2 - second file

first=$(sed -n '/Result:/,$p' "$1")
second=$(sed -n '/Result:/,$p' "$2")

if [ "${first:7}" = "${second:7}" ]; then
    exit 0
else
    exit 1
fi
~                                                                               
~                   
