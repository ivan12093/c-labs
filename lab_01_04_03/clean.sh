#!/bin/bash

to_delete=$(find . -type f -regex ".*\.\(exe\|o\|gcov\|gcna\|gcno\)")

for file in $to_delete; do
	rm "$file"	
done
