/* ex 2.1 pb de couverture d'ensemble  
   modèle implicite avec simplification du fait que nous faisons l'hypoth�se que la matrice creuse est toujours compos�e de 1*/

# Déclaration des données du problème

	param maxSalle;
	set S := 1..maxSalle; # index des salles

	set indCam; # index des caméras
	
	set SCam within S cross indCam; # double-indice des salles et caméras	

	param obj{indCam}; # Vecteur des coefficients de la fonction objectif (indicé sur les caméras)

	param mdroite{S}; # Vecteur des membres de droite des contraintes (indicé sur les salle)


# Déclaration d'un tableau de variables binaires
	
	var x{indCam} binary;	

# Fonction objectif

	minimize cout : sum{j in indCam} obj[j]*x[j];

# Contraintes

	s.t. Salle{i in S} : sum{(i,j) in SCam} x[j] >= mdroite[i]; 

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

	set SCam := (1,*) B E F (2,*) B C D (3,*) D H I (4,*) E G L M (5,*) C F G H J K
                (6,*) I J P (7,*) M N (8,*) K L N O R (9,*) O P Q (10,*) Q R;

	param obj default 1;	

	param mdroite default 1:= 4 2;
	
# Fin

end;

