/* Exercice 1 de la première feuille de TD */

# Déclaration des ensembles et données utilisées

	param nb_casquettes; # taille du problème (nombre de modèles de casquettes)
	param nb_ateliers; # nombre d'ateliers

	set casquettes := 1..nb_casquettes; # ensemble des casquettes
	set ateliers := 1..nb_ateliers; # ensemble des ateliers

	param operations{ateliers, casquettes}; # matrice de la durée des opérations ateliers/casquettes
        param heures_dispo{ateliers}; # quantié d'heures de disponibilité de chaque atelier 
        param prix{casquettes}; # prix de vente de chaque type de casquettes 


# Déclaration des variables
	
	var production_casquettes{casquettes} >= 0, integer; /* Nombre de casquettes produites, pour chaque type */ 

# Fonction objectif

	maximize profit : sum{i in casquettes} prix[i] * production_casquettes[i];

# Contraintes

	s.t. Durees{i in ateliers} : sum{j in casquettes} ( operations[i,j] * production_casquettes[j] ) <= heures_dispo[i];

# Résolution (qui est ajoutée en fin de fichier si on ne le précise pas)
	solve;

# Affichage des résultats
	display : production_casquettes;
	display : profit;
	
# Données

data;

	param nb_casquettes := 2;
	param nb_ateliers := 2;

	param operations : 1   2 :=
                         1 0.2 0.4
                         2 0.2 0.6;
        param heures_dispo := 1 400 2 800;
        param prix := 1 12 2 20;

end;
