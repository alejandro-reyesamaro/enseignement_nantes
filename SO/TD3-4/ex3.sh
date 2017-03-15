#!/bin/sh
if [ $# -eq 2 ]; then 		#si le nombre d'arguments est égal à 2 :
	rep="." 						#variable rep vaut le repertoire courant = "."
	droit=$1						#variable droit vaut le premier argument $1
	ext=$2						#variable ext vaut le deuxieme argument $2
elif [ $# -eq 3 ]; then 	#si le nombre d'arguments est égal à 3 :
	rep=$1						#variable droit vaut le premier argument $1
	droit=$2						#variable droit vaut le deuxieme argument $2
	ext=$3						#variable ext vaut le troisieme argument $3
else
	echo "erreur : donnez 2 ou 3 arguments" 1>&2
	exit 1
fi

for fich in "${rep}"/*"${ext}"; do
chmod g$droit "$fich"
echo $fich
done
