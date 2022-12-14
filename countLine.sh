#!/bin/bash

for f in studies_sampKenj/inputs/parameters/xsec/*; do
	if [[ $f == *.txt ]]
	then
		wc -l $f
	fi
done
