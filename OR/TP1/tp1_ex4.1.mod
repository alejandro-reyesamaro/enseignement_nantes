/* Exercice 4 de la première feuille de TD (première question) */

# Déclaration des ensembles et données utilisées

	param n; # taille du problème (nombre de tranches horaires)
	set tranche := 1..n; # ensemble des tranches horaires
	param service{tranche}; # membre de droite des contraintes

# Déclaration des variables
	
	var x{tranche} >= 0, integer; /* trancheombre d'infirmières débutant dans chaque tranche horaire */
 
# Fonction objectif

	minimize nbInf : sum{i in tranche} x[i];

# Contraintes

	s.t. Tranche{i in tranche} : x[i] + x[(i - 2) mod n + 1] + x[(i - 4) mod n + 1] + x[(i - 5) mod n + 1] >= service[i];

# Résolution (qui est ajoutée en fin de fichier si on ne le précise pas)
	solve;

# Affichage des résultats
	display : x;	# affichage "standard" des variables
	display : nbInf; # affichage de la valeur optimale
	
# Données

data;

	param n := 12;
	param service := 1 35 2 40 3 40 4 35 5 30 6 30 7 35 8 30 9 20 10 15 11 15 12 15;

end;
