#!/bin/sh

for rep in *; do # pour chaque fichier "rep" du repertoire courant
	if [ -f "$rep" ]; then # si rep est un repertoire
	echo $rep # affiche rep
fi
done
