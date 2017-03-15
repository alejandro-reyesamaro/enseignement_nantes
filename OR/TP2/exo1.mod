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

	maximize profit : sum{j in indCol} obj[j]*x[j];

# Contraintes

	s.t. Contrainte{i in indRow} : sum{(i,j) in Matcr} x[j] <= 1; 

# Resolution (qui est ajoutee en fin de fichier si on ne le precise pas)

	solve;

# Affichage des resultats

	display : x;	# affichage "standard" des variables
	display : "objectif : ", profit;

# Données

data;

	param m := 11;
	param n := 9;

	param obj :=	1	1
			2	3
			3	7
			4	3
			5	12
			6	4
			7	9
			8	4
			9	3;

	set Matcr :=	(1,*) 1 5
			(2,*) 2 5
			(3,*) 3 5
			(4,*) 3 4
			(5,*) 2 7
			(6,*) 5 7
			(7,*) 5 4
			(8,*) 6 7
			(9,*) 6 8
			(10,*) 8 4
			(11,*) 5 9;
			
end;



