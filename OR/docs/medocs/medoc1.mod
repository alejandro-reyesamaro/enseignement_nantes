/* Première modélisation avec GNU MathProg 
   Il s'agit d'un modèle totalement explicite */

# Déclaration de variables non-négatives
	
	var x1 >= 0;
	var x2 >= 0;
	var x3 >= 0;
	var x4 >= 0;

# Fonction objectif

	maximize profit : 15*x1 + 60*x2 + 4*x3 + 20*x4;

# Contraintes

	s.t. Toxine1 : 20*x1 + 20*x2 + 10*x3 + 40*x4 <= 21;
	s.t. Toxine2 : 10*x1 + 30*x2 + 20*x3 <= 6;
	s.t. Toxine3 : 20*x1 + 40*x2 + 30*x3 + 10*x4 <= 14;

# Résolution (qui est ajoutée en fin de fichier si on ne le précise pas)
	solve;

# Affichage des résultats
	display : x1,x2,x3,x4; # affichage des variables
	display : 'z=',15*x1 + 60*x2 + 4*x3 + 20*x4; # affichage de la valeur optimale
	
end;
