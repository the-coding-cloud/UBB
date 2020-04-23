#!/bin/bash
for filename in `find`; do
if test -L $filename; then
	if ! test -e $filename; then
		echo $filename
	fi
fi
done
