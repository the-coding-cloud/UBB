#!/bin/bash

while true; do
	for dangerousProcess in $@; do
		dangerousProcessIDs=`ps -a | grep "\<$dangerousProcess\>" | awk '{print $1}'`
		for ID in dangerousProcessIDs; do
			kill -9 $ID
			echo "$dangerousProcess has been killed"
		done
	done
done
