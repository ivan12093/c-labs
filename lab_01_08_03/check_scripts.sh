#!/bin/bash

shell_scripts=$(find . -name "*.sh")


for script in $shell_scripts; do
	shellcheck "$script"
done

