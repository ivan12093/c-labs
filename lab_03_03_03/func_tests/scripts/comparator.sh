#!/bin/bash

# $1 - first file
# $2 - second file

first=$(grep -oE "[+-]?([0-9]+([.][0-9]*)?([eE][+-]?[0-9]+)?|[.][0-9]+([eE][+-]?[0-9]+)?)" "$1")
second=$(grep -oE "[+-]?([0-9]+([.][0-9]*)?([eE][+-]?[0-9]+)?|[.][0-9]+([eE][+-]?[0-9]+)?)" "$2")

if [ "$first" = "$second" ]; then
    exit 0
else
    exit 1
fi
~                                                                               
~                   
