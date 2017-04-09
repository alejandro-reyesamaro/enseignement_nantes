/* 
   GAILLARD Florent
   MONNEAU Dylan 
   601A
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h> /* Bibliothèques utilisées pour mesurer le temps CPU */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

#include "regroupPossible.hpp"
#include "voyageurCommerce.hpp"
#include "partionnement.hpp"

using namespace std;

/* structures et fonctions de mesure du temps CPU */

struct timeval start_utime, stop_utime;

void crono_start()
{
	struct rusage rusage;
	
	getrusage(RUSAGE_SELF, &rusage);
	start_utime = rusage.ru_utime;
}

void crono_stop()
{
	struct rusage rusage;
	
	getrusage(RUSAGE_SELF, &rusage);
	stop_utime = rusage.ru_utime;
}

double crono_ms()
{
	return (stop_utime.tv_sec - start_utime.tv_sec) * 1000 +
    (stop_utime.tv_usec - start_utime.tv_usec) / 1000 ;
}

/* lecture des donnees */

void lecture_data(char *file, donnees *p)
{
	int i,j;
	FILE *fin;
	
	int val;
	fin = fopen(file,"rt");
	
	/* Lecture du nombre de villes */
	
	fscanf(fin,"%d",&val);
	p->nblieux = val;

	/* Allocation mémoire pour la demande de chaque ville, et le distancier */
	
	p->demande = (int *) malloc (val * sizeof(int));
	p->C = (int **) malloc (val * sizeof(int *));
	for(i = 0;i < val;i++) p->C[i] = (int *) malloc (val * sizeof(int));
	
	/* Lecture de la capacité */
	
	fscanf(fin,"%d",&val);
	p->capacite = val;
	
	/* Lecture des demandes des clients */
	
	for(i = 1;i < p->nblieux;i++)
	{ 
		fscanf(fin,"%d",&val);
		p->demande[i] = val;
	}

	/* Lecture du distancier */

	for(i = 0; i < p->nblieux; i++)
		for(j = 0; j < p->nblieux; j++)
		{
			fscanf(fin,"%d",&val);
			p->C[i][j] = val;
		}
		
	fclose(fin);
}

/* Fonction de libération mémoire des données */

void free_data(donnees *p)
{
	int i;
	for(i = 0;i < p->nblieux;i++) free(p->C[i]);
	free(p->C);
	free(p->demande);	
}

int main(int argc, char *argv[])
{	
	/* Déclarations des variables liees aux donnees et aux calculs des chronos */

	donnees p; 

	double temps;
	double temps1;
	double temps2;
	double temps3;
	
	/* Chargement des données à partir d'un fichier */
	
	lecture_data(argv[1],&p);
	
	/* Lancement de la résolution... */


	/* ------------------ Regroupements possibles ------------------ */


	crono_start(); // .. et donc du chronomètre

	printf("------------------ Calcul des regroupements possibles ------------------\n");

	/* calcul des tous les regroupements possibles ne depassant pas la capacité du drone */

	vector<vector<int> > regroup = regroupementPossible(p);

	crono_stop();
	temps1 = crono_ms() / 1000,0;
	printf("Temps 1 : %lf\n", temps1);


	/* ------------------ Voyageur du commerce ------------------ */


	crono_start();

	printf("------------------ Calcul des plus courtes distances ------------------\n");

	double *distancesMin = (double *) malloc (regroup.size() * sizeof(double));
	distancesMin = voyageurDuCommerce(regroup, p);

	crono_stop();
	temps2 = crono_ms() / 1000,0;
	printf("Temps 2 : %lf\n", temps2);
 

	/* ------------------ Partitionnement des tournees ------------------ */


	crono_start();

	printf("------------------ Partitionnement des tournees ------------------\n");

	partionnementTournees(regroup, distancesMin, p);

	/* Problème résolu, arrêt du chrono */
	
	crono_stop();
	temps3 = crono_ms()/1000,0;
	temps = temps1 + temps2 + temps3;
	
	/* Affichage des résultats (à compléter) */
	
	printf("Temps total : %f\n",temps);	
	
	/* libération mémoire (à compléter en fonction des allocations) */

	free_data(&p);
	
	/* J'adore qu'un plan se déroule sans accroc! */
	return 0;
}
