/* ex 2.1 pb de couverture d'ensemble  
   modèle implicite avec simplification du fait que nous faisons l'hypoth�se que la matrice creuse est toujours compos�e de 1*/

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

	param obj default 1;	

	param coeffcontr default 1;

	param mdroite default 1:= 4 2;
	
# Fin

end;

