/* Exercice 5 de la première feuille de TD */

# Déclaration des ensembles et données utilisées

	param nbPeriodes; # Nombres de périodes considérées
	set Periodes := 1..nbPeriodes; # Ensemble des périodes considérées
	set Periodes2 := 2..nbPeriodes; # Ensemble des périodes considérées à l'exclusion de la première	
	param ProdMax; # Production maximale en heures normales
	param StockInit; # Stock initial
	param CoutNormal; # Coût de production d'un vélo en heures normales
	param CoutSup; # Coût de production d'un vélo en heures sup
	param CoutStock; # Coût de stockage d'un vélo
	param d{Periodes}; # demande pour chaque période

# Déclaration des variables
	
	var xN{Periodes} >= 0, integer; /* Nombre de vélos produits en heures normales pour chaque période */
	var xS{Periodes} >= 0, integer; /* Nombre de vélos produits en heures supplémentaires pour chaque période */
	var s{Periodes} >= 0, integer; /* Nombre de vélos stockés à la fin de chaque période */ 

# Fonction objectif

	minimize cout : sum{i in Periodes} (CoutNormal*xN[i] + CoutSup*xS[i] + CoutStock*s[i]);

# Contraintes

	s.t. Equilibre1 : xN[1] + xS[1] + StockInit = d[1] + s[1];
	s.t. Equilibre{i in Periodes2} : xN[i] + xS[i] + s[i-1] = d[i] + s[i];
	s.t. LimitProd{i in Periodes} : xN[i] <= ProdMax;

# Résolution (qui est ajoutée en fin de fichier si on ne le précise pas)
	solve;

# Affichage des résultats
	display : xN,xS,s;	# affichage "standard" des variables
	display : sum{i in Periodes} (CoutNormal*xN[i] + CoutSup*xS[i] + CoutStock*s[i]); # affichage de la valeur optimale
	
# Données

data;

	param nbPeriodes := 12;
	param ProdMax := 30000;
	param StockInit := 2000;
	param CoutNormal := 20;
	param CoutSup := 30;
	param CoutStock := 3;
	param d := 1 30000 2 15000 3 15000 4 25000 5 33000 6 40000 7 45000 8 45000 9 26000 10 14000 11 25000 12 30000; 	

end;
