/* ex 2.2 pb de couverture d'ensemble  
   modèle implicite */

# Déclaration des données du problème

	param maxSalle;
	set S := 1..maxSalle; # indices des salles

	set indCam; # indices des caméras

	param obj{indCam}; # Vecteur des coefficients de la fonction objectif (indicé sur les caméras)

	param coeffcontr{S,indCam}; # Matrice des coefficients définissant les membres de gauche des contraintes (double-indice)

	param mdroite{S}; # Vecteur des membres de droite des contraintes (indicé sur les salle)


# Déclaration d'un tableau de variables binaires
	
	var x{indCam} binary;	

# Fonction objectif

	minimize cout : sum{j in indCam} obj[j]*x[j];

# Contraintes

	s.t. Salle{i in S} : sum{j in indCam} coeffcontr[i,j] * x[j] >= mdroite[i]; 

# Résolution (qui est ajoutée en fin de fichier si on ne le précise pas)

	solve;

# Affichage des résultats

	display : x;	# affichage "standard" des variables
	display{j in indCam : x[j] = 1} : j; # affichage plus lisible  
	display : "objectif : ", sum{j in indCam} obj[j]*x[j];

# données numériques dont le début est indiqué par le mot-clé "data;"

data;

	param maxSalle := 10;
	
	set indCam := B C D E F G H I J K L M N O P Q R;

	param obj := B 1 C 1 D 1 E 1 F 1 G 1 H 1 I 1 J 1 K 1 L 1 M 1 N 1 O 1 P 1 Q 1 R 1;	

	param coeffcontr :  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R :=
	                 1  1  0  0  1  1  0  0  0  0  0  0  0  0  0  0  0  0
	                 2  1  1  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0
	                 3  0  0  1  0  0  0  1  1  0  0  0  0  0  0  0  0  0
	                 4  0  0  0  1  0  1  0  0  0  0  1  1  0  0  0  0  0
	                 5  0  1  0  0  1  1  1  0  1  1  0  0  0  0  0  0  0
	                 6  0  0  0  0  0  0  0  1  1  0  0  0  0  0  1  0  0
	                 7  0  0  0  0  0  0  0  0  0  0  0  1  1  0  0  0  0
	                 8  0  0  0  0  0  0  0  0  0  1  1  0  1  1  0  0  1
	                 9  0  0  0  0  0  0  0  0  0  0  0  0  0  1  1  1  0
	                 10 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1  1;

	param mdroite := 1  1
	                 2  1
	                 3  1
	                 4  2
	                 5  1
	                 6  1
	                 7  1
	                 8  1
	                 9  1
	                 10 1;

# Fin

end;
