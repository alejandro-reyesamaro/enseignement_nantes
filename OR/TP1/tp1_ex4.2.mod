/* Exercice 4 de la première feuille de TD (seconde question) */

# Déclaration des ensembles et données utilisées

	param n; # taille du problème (nombre de tranches horaires)
	set tranche := 1..n; # ensemble des tranches horaires
	param service{tranche}; # membre de droite des contraintes
	param nbInf; # nombre d'infirmière (qui devient une donnée dans cette seconde question)

# Déclaration des variables
	
	var normal{tranche} >= 0, integer; /* Nombre d'infirmières débutant dans chaque tranche horaire */
	var sup{tranche} >= 0, integer; /* Nombre d'infirmières débutant dans chaque tranche horaire et effectuant des heures sup */

# Fonction objectif

	minimize nbSup : sum{i in tranche} sup[i];

# Contraintes

	s.t. Tranche{i in tranche} : normal[i] + normal[(i - 2) mod n + 1] + normal[(i - 4) mod n + 1] + normal[(i - 5) mod n + 1] + sup[(i - 6) mod n + 1] >= service[i];
	s.t. ContrtranchebInf : sum{i in tranche} normal[i] <= nbInf;
	s.t. InfSup{i in tranche} : sup[i] <= normal[i]; 

# Résolution (qui est ajoutée en fin de fichier si on ne le précise pas)
	solve;

# Affichage des résultats
	display : normal;
	display : sup;
	display : nbSup; # affichage de la valeur optimale
	
# Données

data;

	param n := 12;
	param service := 1 35 2 40 3 40 4 35 5 30 6 30 7 35 8 30 9 20 10 15 11 15 12 15;
	param nbInf := 80;

end;
