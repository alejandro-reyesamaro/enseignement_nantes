/* ecriture generique du probleme de couverture d'ensemble,
   les coefficients de la matrice creuse sont necessairement des 1,
   les membres droits des contraintes sont necessairement des 1 */

# Declaration des donnees du probleme

	param m; # nombre de contraintes (lignes) du probleme
	param n; # nombre de variables (colonnes) du probleme

	set indRow := 1..m; # indices des contraintes
	set indCol := 1..n; # indices des variables

	set Matcr dimen 2; # Matrice creuse des contraintes	

	param obj{indCol}; # Vecteur des coefficients de la fonction objectif 

# Declaration d'un tableau de variables binaires
	
	var x{indCol} binary;	

# Fonction objectif

	minimize cout : sum{j in indCol} obj[j]*x[j];

# Contraintes

	s.t. Contrainte{i in indRow} : sum{(i,j) in Matcr} x[j] >= 1; 

# Resolution (qui est ajoutee en fin de fichier si on ne le precise pas)

	solve;

# Affichage des resultats

	display : x;	# affichage "standard" des variables
	display : "objectif : ", sum{j in indCol} obj[j]*x[j];

end;

