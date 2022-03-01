#!/bin/bash

shell_scripts=$(find . -name "*.sh")
echo -e "$shell_scripts"

for script in $shell_scripts; do
	shellcheck "$script"
done

