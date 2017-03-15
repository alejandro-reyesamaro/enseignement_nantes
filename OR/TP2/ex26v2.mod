/* Modélisation de l'exercice 2.6 avec GNU MathProg 
   (version avec des variables déclarées pour toutes les livraisons, même si elles sont impossibles) */

# Déclaration des ensembles et données utilisées

	param n; # Nombre d'entrepôts 
	param m; # nombre de clients 
	set N := 1..n; # Ensemble des indices des entrepôts 
	set M := 1..m; # Ensemble des indices des clients 
	set NM within N cross M; # Déclaration d'un ensemble d'indice de dimension 2 (précondition ajoutée : sous-ensemble de N * M) 
	param f{N}; # les f_i de la modélisation (coûts des ouvertures des entrepôts)
	param c{NM}; # les c_{ij} de la modélisation (coûts des livraisons)
	param d{M}; # les d_j de la modélisation (demande des clients)
	param Ca{N}; # les Ca_i de la modélisation (capacité des entrepôts)

# Déclarations des variables 

	var x{NM} >=0; # x_{ij}
	var y{N} binary; # y_i

# Fonction objectif 

	minimize cout : (sum{i in N} f[i]*y[i]) + (sum{(i,j) in NM} c[i,j]*x[i,j]);

# Contraintes 

	s.t. BorneSupX{(i,j) in NM} : x[i,j] <= 1;
	s.t. SatisfactionDemande{j in M} : sum{(i,j) in NM} x[i,j] = 1;
	s.t. LimiteCapacite{i in N} : sum{(i,j) in NM} d[j]*x[i,j] <= Ca[i]*y[i];

# Résolution 

	solve;

# Affichage des résultats 

	display : x;	
	display : y;
	display : "objectif : ", (sum{i in N} f[i]*y[i]) + (sum{(i,j) in NM} c[i,j]*x[i,j]);

# Données

data;

	param n := 12;
	param m := 12;

	set NM := 	(1,*) 1 2 3 4 5 6 7 8 9 10 11 12
		 		(2,*) 1 2 3 4 5 6 7 8 9 10 11 12 
		 		(3,*) 1 2 3 4 5 6 7 8 9 10 11 12
		 		(4,*) 1 2 3 4 5 6 7 8 9 10 11 12
		 		(5,*) 1 2 3 4 5 6 7 8 9 10 11 12
		 		(6,*) 1 2 3 4 5 6 7 8 9 10 11 12
		 		(7,*) 1 2 3 4 5 6 7 8 9 10 11 12
		 		(8,*) 1 2 3 4 5 6 7 8 9 10 11 12
		 		(9,*) 1 2 3 4 5 6 7 8 9 10 11 12
		 		(10,*) 1 2 3 4 5 6 7 8 9 10 11 12
		 		(11,*) 1 2 3 4 5 6 7 8 9 10 11 12
		 		(12,*) 1 2 3 4 5 6 7 8 9 10 11 12;

	param f :=  1	3500
				2	9000
				3	10000
				4	4000
				5	3000
				6	9000
				7	9000
				8	3000
				9	4000
				10	10000
				11	9000
				12	3500;


	param c :=	[1,1] 100 [1,2] 80 [1,3] 50 [1,4] 50 [1,5] 60 [1,6] 100 [1,7] 120 [1,8] 90 [1,9] 60 [1,10] 70 [1,11] 65 [1,12] 110
				[2,1] 120 [2,2] 90 [2,3] 60 [2,4] 70 [2,5] 65 [2,6] 110 [2,7] 140 [2,8] 110 [2,9] 80 [2,10] 80 [2,11] 75 [2,12] 130 
				[3,1] 140 [3,2] 110 [3,3] 80 [3,4] 80 [3,5] 75 [3,6] 130 [3,7] 160 [3,8] 125 [3,9] 100 [3,10] 100 [3,11] 80 [3,12] 150
				[4,1] 160 [4,2] 125 [4,3] 100 [4,4] 100 [4,5] 80 [4,6] 150 [4,7] 190 [4,8] 150 [4,9] 130 [4,10] 50000 [4,11] 50000 [4,12] 50000
				[5,1] 190 [5,2] 150 [5,3] 130 [5,4] 50000 [5,5] 50000 [5,6] 50000 [5,7] 200 [5,8] 180 [5,9] 150 [5,10] 50000 [5,11] 50000 [5,12] 50000
				[6,1] 200 [6,2] 180 [6,3] 150 [6,4] 50000 [6,5] 50000 [6,6] 50000 [6,7] 100 [6,8] 80 [6,9] 50 [6,10] 50 [6,11] 60 [6,12] 100
				[7,1] 100 [7,2] 80 [7,3] 50 [7,4] 50 [7,5] 60 [7,6] 100 [7,7] 120 [7,8] 90 [7,9] 60 [7,10] 70 [7,11] 65 [7,12] 110
				[8,1] 120 [8,2] 90 [8,3] 60 [8,4] 70 [8,5] 65 [8,6] 110 [8,7] 140 [8,8] 110 [8,9] 80 [8,10] 80 [8,11] 75 [8,12] 130
				[9,1] 140 [9,2] 110 [9,3] 80 [9,4] 80 [9,5] 75 [9,6] 130 [9,7] 160 [9,8] 125 [9,9] 100 [9,10] 100 [9,11] 80 [9,12] 150
				[10,1] 160 [10,2] 125 [10,3] 100 [10,4] 100 [10,5] 80 [10,6] 150 [10,7] 190 [10,8] 150 [10,9] 130 [10,10] 50000 [10,11] 50000 [10,12] 50000
				[11,1] 190 [11,2] 150 [11,3] 130 [11,4] 50000 [11,5] 50000 [11,6] 50000 [11,7] 200 [11,8] 180 [11,9] 150 [11,10] 50000 [11,11] 50000 [11,12] 50000
				[12,1] 200 [12,2] 180 [12,3] 150 [12,4] 50000 [12,5] 50000 [12,6] 50000 [12,7] 100 [12,8] 80 [12,9] 50 [12,10] 50 [12,11] 60 [12,12] 100;

	param d :=	1	120
				2	80
				3	75
				4	100
				5	110
				6	100
				7	90
				8	60
				9	30
				10	150
				11	95
				12	120;

	param Ca :=	1	300
				2	250
				3	100
				4	180
				5	275
				6	300
				7	200
				8	220
				9	270
				10	250
				11	230
				12	180;
end;

