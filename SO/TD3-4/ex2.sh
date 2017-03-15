#!/bin/sh
w=`who | grep $1`
w=$(who | grep $1)
if [ -z "$w" ]; then 
	echo "$1 n'est pas connecté"; 
fi
