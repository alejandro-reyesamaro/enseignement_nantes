/* ex 2.1 pb de couverture d'ensemble  
   modèle implicite avec utilisation d'une matrice creuse */

# Déclaration des données du problème

	param maxSalle;
	set S := 1..maxSalle; # index des salles

	set indCam; # index des caméras
	
	set SCam within S cross indCam; # double-indice des salles et caméras	

	param obj{indCam}; # Vecteur des coefficients de la fonction objectif (indicé sur les caméras)

	param coeffcontr{(i,j) in SCam}; # Matrice des coefficients définissant les membres de gauche des contraintes (double-indice)

	param mdroite{S}; # Vecteur des membres de droite des contraintes (indicé sur les salle)


# Déclaration d'un tableau de variables binaires
	
	var x{indCam} binary;	

# Fonction objectif

	minimize cout : sum{j in indCam} obj[j]*x[j];

# Contraintes

	s.t. Salle{i in S} : sum{(i,j) in SCam} coeffcontr[i,j] * x[j] >= mdroite[i]; 

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

	set SCam := (1,B) (1,E) (1,F) (2,B) (2,C) (2,D) (3,D) (3,H) (3,I) (4,E) (4,G) (4,L) (4,M) (5,C) (5,F) (5,G) (5,H) (5,J) (5,K)
                (6,I) (6,J) (6,P) (7,M) (7,N) (8,K) (8,L) (8,N) (8,O) (8,R)	(9,O) (9,P) (9,Q) (10,Q) (10,R);

	param obj := B 1 C 1 D 1 E 1 F 1 G 1 H 1 I 1 J 1 K 1 L 1 M 1 N 1 O 1 P 1 Q 1 R 1;	

	param coeffcontr := [1,B] 1 [1,E] 1 [1,F] 1 [2,B] 1 [2,C] 1 [2,D] 1 [3,D] 1 [3,H] 1 [3,I] 1 
						[4,E] 1 [4,G] 1 [4,L] 1 [4,M] 1 [5,C] 1 [5,F] 1 [5,G] 1 [5,H] 1 [5,J] 1 [5,K] 1
	                    [6,I] 1 [6,J] 1 [6,P] 1 [7,M] 1 [7,N] 1 [8,K] 1 [8,L] 1 [8,N] 1 [8,O] 1
	                    [8,R] 1 [9,O] 1 [9,P] 1 [9,Q] 1 [10,Q] 1 [10,R] 1;

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

