/*

Projet RO 2017
Chedotal Corentin & Duclos Romain - 601A

Fichier bladeflyerii.cpp :

Fichier principal du projet.
Contient le main et l'appel au solveur glpk.

*/

//Bibliothèque GLPK
#include <glpk.h>


#include <iostream>

//Nos algorithmes et structures de données
#include "gestion_donnees.hpp"
#include "tsp_brute_force.hpp"

//time(), clock_t, clock(), CLOCKS_PER_SEC
#include <ctime>     

using namespace std;

// Eléments de mesure de performance
clock_t chrono;

//Démarre le chronomètre
#define START chrono=clock();

//Arrête le chronomètre
#define STOP chrono=clock()-chrono;

//Donne le temps du chronomètre (après arrêt)
#define TEMPS double(chrono)/CLOCKS_PER_SEC;

int main(int argc, char const *argv[])
{
	//Données tirées du fichier
	donnees_f f;

	//Données pour le problème
	donnees_p p;

	//Pointeur sur le problème
	glp_prob *prob;

	//Variables de boucles
	int i;
	int j;

	//Variables pour la récupération des résultats
	double z;
	vector<int> x;

	//Déclaration et allocation mémoire des trois tableaux de la matrice creuse des contraintes
	int *ia;
	int *ja;
	double *ar;

	//Récupération des données
	lecture_data(argv[1],f);

	//On démarre les algorithmes et la résolution du problème
	//-> début du chrono
	START;

	remplis_donnees(p,f);

	//Allocation mémoire au problème
	prob = glp_create_prob();

	//Affectation d'un nom
	glp_set_prob_name(prob, "BladeFlyerII");

	//Sens d'optimisation
	glp_set_obj_dir(prob, GLP_MIN);

	//On a une contrainte pour chaque point de pompage
	//donc n contraintes
	glp_add_rows(prob, p.nbvar);

	//Bornes sur les contraintes
	//ici, elles sont toutes du type =1
	for (i = 0; i < p.nbvar; ++i)
	{
		glp_set_row_bnds(prob,i,GLP_FX,1.0,0.0);
	}

	//On nbvar de décision (c'est le nombre de regroupement)
	//Donc nbvar colonnes
	glp_add_cols(prob, p.nbvar);

	//Pour chaque variable
	for(i = 1; i <= p.nbvar; ++i)
	{
		//Bornes sur les variables 0 <= xi <= 1
		glp_set_col_bnds(prob,i,GLP_DB,0.0,1.0);
	
		//Type des variables (ici binaire -> GLP_BV)
		glp_set_col_kind(prob,i,GLP_BV);

	}

	//Coefficients des variables dans la fonction objectif
	//Ici li est la distance minimale pour le regroupement i
	for(i = 1;i <= p.Pn;i++) glp_set_obj_coef(prob,i,p.couts[i - 1]);

	//Gestion matrice creuse des contraintes

	//Allocation mémoire pour les trois tableaux, ia, ja et ar pour la matrice creuse
	ia = (int *) malloc ((1 + p.nbcreux) * sizeof(int));
	ja = (int *) malloc ((1 + p.nbcreux) * sizeof(int));
	ar = (double *) malloc ((1 + p.nbcreux) * sizeof(double));
	
	pos = 1;
	//On a nbcontr contraintes
	for (i = 0; i < p.nbcontr; ++i)
	{
		//Pour chacune des contraintes on récupère les indices des variables dans le tableau des contraintes
		for (j = 0; i < p.contr[i].size(); ++i)
		{
			ia[pos] = i;
			ja[pos] = p.contr[i][j];
			ar[pos] = 1.0;
			pos++;
		}
	}

	//Chargement de la matrice dans le problème
	glp_load_matrix(prob,p.nbcreux,ia,ja,ar);

	//Ecriture de la résolution dans un fichier
	glp_write_lp(prob,NULL,"BladeFlyerII.lp");

	//Résolution
	glp_simplex(prob,NULL);
	glp_intotp(prob,NULL);

	//Récupération du résultat
	z = glp_mip_obj_val(prob); //Valeur optimale
	for (i = 0; i < p.nbvar; ++i) x.push_back(glp_mip_col_val(prob,i+1)); //Valeur de chaque variable

	
	//Problème résolu, arrêt du chrono
	STOP;

	//Affichage des résultats

	//Temps
	cout << "Temps total de résolution : " << TEMPS << "s" << endl;

	//Résultats du problème
	cout << "z = " << z << endl;
	for (i = 0; i < p.nbvar; ++i)
	{
		cout << "x" << i << " = " << x[i] << endl;
	}
	
	//Libération de la mémoire
	glp_delete_prob(prob);

	//Fin
	return 0;


}//Fermeture du main
