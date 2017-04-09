//NAFTI Slimen 601B

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h> /* Bibliothèques utilisées pour mesurer le temps CPU */

#include <list>
#include <iostream>
#include "calcul.hpp"

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

	// Lecture du nombre de puits 

	fscanf(fin,"%d",&val);
	p->quantpuit = val;

	// Allocation mémoire pour la demande de chaque puit

	p->demande = (int *) malloc (val * sizeof(int));
	p->C = (int **) malloc (val * sizeof(int *));
	for(i = 0;i < val;i++) p->C[i] = (int *) malloc (val * sizeof(int));

	// Lecture de la capaciteStockageDrone */

	fscanf(fin,"%d",&val);
	p->capaciteStockageDrone = val;

	// Lecture des demandes des puits

	for(i = 1;i < p->quantpuit;i++)
	{
		fscanf(fin,"%d",&val);
		p->demande[i] = val;
	}

	

	for(i = 0; i < p->quantpuit; i++)
		for(j = 0; j < p->quantpuit; j++)
		{
			fscanf(fin,"%d",&val);
			p->C[i][j] = val;
		}

	fclose(fin);
}

// Fonction de libération mémoire des données

void libereMem(donnees *p)
{
	int i;
	for(i = 0;i < p->quantpuit;i++) free(p->C[i]);
	free(p->C);
	free(p->demande);
}


int main(int argc, char *argv[])
{
	/* Déclarations des variables (à compléter) */

	donnees p;
	double temps;
	list< list<int> > ec;
	list<regroupement> res;

	/* Chargement des données à partir d'un fichier */

	lecture_data(argv[1],&p);

	/* Lancement de la résolution... */
	crono_start(); // .. et donc du chronomètre
	cout << "Enumération des regroupements de puits..." <<endl;
	// Enumeration
	ec = regroupementP(p.demande, p.quantpuit, p.capaciteStockageDrone);
	afficheListeBis(ec);
	cout << "**************************************"<<endl;

	// Les permutations
	cout << "Calcule des distances la plus courte des regroupements..." <<endl;
	res = echangerDeuxFois(ec, (const int**) p.C);
	afficheListe(res);
	cout << "***************************************"<<endl;


	/* problème de minimisation (glpk) */
	cout << "Résoltion du Problème"<<endl;
	resolution(res, p);


	/* Problème résolu, arrêt du chrono */
	crono_stop();
	temps = crono_ms()/1000,0;

	/* Affichage des résultats (à compléter) */
	printf("Temps : %f\n",temps);

	/* libération mémoire (à compléter en fonction des allocations) */
	libereMem(&p);
	return 0;
}

