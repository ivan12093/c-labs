#!/bin/bash

# $1 - first file
# $2 - second file

first="$(sed -n -e '/Result:/,$p' "$1")"
second="$(sed -n -e '/Result:/,$p' "$2")"

if [ "${first:8}" = "${second:8}" ]; then
    exit 0
else
    exit 1
fi
~                                                                               
~                   
