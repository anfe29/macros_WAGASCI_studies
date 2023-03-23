#!/bin/bash

#for f in studies_sampKenj/inputs/parameters/xsec/*; do
for f in xsec_sampKenj/inputs/splines/*; do
	if [[ $f == *.txt ]]
	then
		wc -l $f
	fi
done
