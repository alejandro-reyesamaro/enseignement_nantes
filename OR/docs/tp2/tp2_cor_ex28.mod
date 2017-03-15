/* Modélisation de l'exercice 2.8 avec GNU MathProg */


# Déclaration des ensembles et données utilisées

	set Villes; # Ensemble des villes
	param pop{Villes}; # les pop_j de la modélisation
	
	set S within Villes cross Villes; # ensemble des double-indices définissant la partie non-creuse de la matrice creuse

# Déclarations des variables 
	
	var y{Villes} binary; # les variables y_i 
	var x{Villes} binary; # les variables x_i

# Fonction objectif

	maximize population : sum{j in Villes} pop[j]*x[j];

# Contraintes

	s.t. ville{i in Villes} : x[i] <= sum{(i,j) in S} y[j]; 
	s.t. last : sum{j in Villes} y[j] = 2;

# Résolution (qui est ajoutée en fin de fichier si on ne le précise pas)

	solve;

# Affichage des résultats

	display : x;	
	display : y;
	display : "objectif : ", sum{j in Villes} pop[j]*x[j];

# données numériques dont le début est indiqué par le mot-clé "data;"

data;

	
	set Villes := A B C D E F G H I J K L M;

	set S := (A,*) A B C D (B,*) A B C D E F G (C,*) A B C D (D,*) A B C D E F G J K (E,*) B D E F G I J K
                (F,*) B D E F G I J K (G,*) B D E F G H I J K (H,*) G H I J K L M (I,*) E F G H I J K L (J,*) D E F G H I J K L (K,*) D E F G H I J K L (L,*) H I J K L M (M,*) H L M;
	
	param pop := A 53 B 46 C 16 D 28 E 96 F 84 G 32 H 21 I 15 J 22 K 41 L 53 M 66;
	
# Fin

end;

