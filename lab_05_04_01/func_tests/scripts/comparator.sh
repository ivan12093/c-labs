#!/bin/bash

# $1 - first file
# $2 - second file

if diff "$1" "$2"; then
    exit 0
else
    exit 1
fi
