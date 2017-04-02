/* Fichier contenant toutes les structures, fonction, librairies communes aux différentes fonctions par : Auffray Baptiste et Dromigny--Chevreuil Ivan */

#ifndef STRUCTURE_H                                                                 
#define STRUCTURE_H  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <numeric>
#include <cmath>


/* Structure contenant les données du problème */

struct donnees {
	int nbLieux; 									// Nombre de lieux (incluant le dépôt) /n
	int capacite; 									// Capacité du véhicule de livraison /Ca
	int nbCirc; 									// Nombre de circuit
	std::vector<int> quantite; 						// Quantité d'eau de chaque lieu (la case 0 est inutilisée car le dépôt n'a aucune quantite d'eau à récuperer) /di
	std::vector <std::vector<int> > distances; 		// Distancier (les lignes et colonnes 0 correspondent au dépôt) /Cij
	std::vector <std::vector<int> > circuit;		// Tableau contenant tous les circuits possibles
	std::vector <std::vector<int> > contr;			// Matrice creuse des contraintes
	std::vector<int> tailleCirc;					// Distance minimale du circuit
};


unsigned int factorial(unsigned int n);

void lecture_data(std::string file, donnees &p);

void regrouper(donnees &p);


#endif //STRUCTURE_H