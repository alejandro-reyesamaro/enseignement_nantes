/* NOM1 Prénom1
   NOM2 Prénom2 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h> /* Bibliothèques utilisées pour mesurer le temps CPU */

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

/* Structure contenant les regroupements du problème */
typedef struct {
	int *longueur; // Longueur du minimale tour du regroupement i 
	int **tab; // Regroupement
	int *n; // Nombre  d'éléments dans le regroupement i
} groupe;

/* Structure contenant les données du problème */
typedef struct {
	int nblieux; // Nombre de lieux (incluant le dépôt) 
	int capacite; // Capacité du véhicule de livraison 
	int *demande; // Demande de chaque lieu (la case 0 est inutilisée car le dépôt n'a aucune demande à voir satisfaire) 
	int **C; // distancier (les lignes et colonnes 0 correspondent au dépôt) 
	int nbcontr; // Nombre de contraintes 
	int nbvar; // Nombre de variables
	groupe regroupe;
} donnees;

/**---------------------------------------------------------------------------------------------------
 * @brief Lecture des données du fichier file et remplissage de la structure p avec les données lues
 *
 * @param file Le fichier passé en paramètre du programme
 * @param p La structure de données à remplir
 *
 * @b Complexité O(1) en fonction du fichier
**/
void lecture_data(char *file, donnees *p)
{
	int i,j, val;
	FILE *fin;
	
	fin = fopen(file,"rt");
	
	/* Lecture du nombre de villes */
	fscanf(fin,"%d",&val);
	p->nblieux = val;

	// Declaration du nombre de contraintes (nombre de lignes de la matrice des contraintes)
	// Il y a une contrainte par nombre de points de pompage
	p->nbcontr = p->nblieux-1;

	/* Allocation mémoire pour la demande de chaque ville, et le distancier */
	
	p->demande = (int *) malloc (val * sizeof(int));
	p->C = (int **) malloc (val * sizeof(int *));
	for(i = 0;i < val;++i) p->C[i] = (int *) malloc (val * sizeof(int));
	
	/* Lecture de la capacité */
	fscanf(fin,"%d",&val);
	p->capacite = val;
	
	/* Lecture des demandes des clients */
	for(i = 1;i < p->nblieux;++i)
	{
		fscanf(fin,"%d",&val);
		p->demande[i] = val;
	}
	
	/* Lecture du distancier */
	for(i = 0; i < p->nblieux; ++i)
		for(j = 0; j < p->nblieux; ++j)
		{
			fscanf(fin,"%d",&val);
			p->C[i][j] = val;
		}
		
	fclose(fin);
}

/**---------------------------------------------------------------------------------------------------
 * @brief Libération des cases mémoires alloués pour les données p
 *
 * @param p Structure de données à désallouer
 *
 * @b Complexité O(p)
**/
void free_data(donnees *p)
{
	int i;
	for(i = 0;i < p->nblieux;++i) free(p->C[i]);
	free(p->C);
	free(p->demande);	
}

/**---------------------------------------------------------------------------------------------------
 * @brief Calcule la longueur minimale du regroupement
 *
 * @param tab Tableau contenant les éléments qui ne sont pas encore dans la combinaison
 * @param tab2 Tableau contenant les éléments d'une combinaison testée
 * @param taille1 Nombre d'éléments dans le regroupement
 * @param taille2 Nombre d'éléments dans tab2
 * @param p Structure contenant les données du problème
 *
 * @return La longueur minimale du regroupement
 *
 * @b Complexité O(taille1!)
**/
int combinaisons(int *tab, int *tab2, int taille1, int taille2, donnees *p)
{
	int i, j, longueur, min, *tab3;

	min = 0;
	longueur = 0;
	// taille2 est égale à taille1 ?
	if (taille2==taille1)
	{
		// Oui : Parcours de tab2 et calcule de la longueur de cette permutation
		for(i=0 ; i<taille1 ; ++i)
		{
			if(i == 0)
			{
				// Ajout de la longueur de la base vers le point de pompage tab2[i]
				longueur = longueur + p->C[0][tab2[i]];
			}
			else
			{
				longueur = longueur + p->C[tab2[i-1]][tab2[i]];
			}
		}
		// Ajout de la longueur du point de pompage tab2[taille1-1] vers la base  
		longueur = longueur + p->C[tab2[taille1-1]][0];
		return longueur;
	} 
	else
	{
		// Non : Parcours du nombre d'éléments restants à rajouter à tab2
		for(i=0; i<(taille1-taille2); ++i)
		{
			tab3 = (int *) malloc((taille1-taille2)*sizeof(int));
			tab2[taille2] = tab[i];
			for(j=0 ; j<i; ++j)
			{
				tab3[j] = tab[j];
			}
			for(j=i ; j<(taille1-taille2)-1; ++j)
			{
				tab3[j] = tab[j+1];
			}

			longueur = combinaisons(tab3, tab2, taille1, taille2+1, p);

			// Est ce que c'est la première longueur calculée ?
			if(i == 0)
			{
				// Oui : c'est la longueur minimale
				min = longueur;
			} 
			else if(longueur < min) // Sinon est ce qu'elle est inférieur à la longueur minimale
			{
				// Oui : c'est la longueur minimale
				min = longueur;
			}

			// Libération du tableau alloué
			free(tab3);
		}
		return min;
	} 
   
}

/**---------------------------------------------------------------------------------------------------
 * @brief Remplit le tableau de regroupement de taille i
 *
 * @param p Structure contenant les données du problème
 * @param i Nombre d'éléments voulus dans les regroupements
 * @param pos Indice du regroupement
 * @param k Nombre d'éléments dans le tableau L
 * @param L Tableau temporaire des regroupements
 * @param t Tableau des indices des points de pompages
 * @param r Nombre de points de pompages restants à mettre dans le regroupements
 *
 * @return Le nombre de regroupement dans la structure p.regroupe
 *
 * @b Complexité O(2^(p.nblieux-1))
**/
int regroupement(donnees *p, int i, int pos, int k, int *L, int *t, int r)
{

	int j, l, j1, t2[p->nblieux-1];
	int  *tab;
	int quantite = 0;
	// Nombre d'éléments voulus égale au nombre d'éléments dans L ?
	if(k == i)
	{
		// Oui : Réallocation des tableaux de taille pos+1
		p->regroupe.longueur = (int *) realloc (p->regroupe.longueur, (pos+1) * sizeof(int));
		p->regroupe.n = (int *) realloc (p->regroupe.n, (pos+1) * sizeof(int));
		p->regroupe.tab = (int **) realloc (p->regroupe.tab, (pos+1) * sizeof(int *));

		p->regroupe.n[pos] = i;
 
		// Allocation du tableau qui contient les indices du regroupement
		p->regroupe.tab[pos] = (int *) malloc (i*sizeof(int));  
		for(j=0 ; j<i; ++j)
		{
			p->regroupe.tab[pos][j] = L[j];
			quantite = quantite + p->demande[L[j]];
		}

		// La somme des quantités d'eau en chaque point de pompage du regroupement est inférieur ou égale à la capacité du drone ?
		if(quantite<=p->capacite)
		{
			// Oui : Calcule de la longueur minimale du regroupement
			tab = (int *) malloc(p->regroupe.n[pos]*sizeof(int));

			p->regroupe.longueur[pos] = combinaisons(p->regroupe.tab[pos], tab, p->regroupe.n[pos], 0, p);

			free(tab);
			pos++;
		} 
		else
		{
			// Non : Libération du tableau alloué
			free(p->regroupe.tab[pos]);
		}
	}
	else
	{
		// Non : Rappel de la fonction sur le nombre de points de pompages restants
		for(l=0 ; l<r ; ++l)
		{
			// Ajout du points de pompage t[l] dans le regroupement L
			L[k] = t[l];

			// Copie du tableau t dans t2 en elevant t[l]
			for(j=l+1, j1=0;j<r;j++, j1++) 
			{
				t2[j1] = t[j];
			}
			pos = regroupement(p, i, pos, k+1, L, t2, j1);
		}
	}

	return pos;
} 

/**---------------------------------------------------------------------------------------------------
 *
 *
 *
 *
**/
int main(int argc, char *argv[])
{	
	/* Déclarations des variables */

	donnees p; // Données du probleme
	double temps;

	/* Structures de données propres à GLPK */
	
	glp_prob *prob; // Déclaration d'un pointeur sur le problème

	/* Déclaration des 3 tableaux servant à définir la matrice "creuse" des contraintes */
	int *lignes;
	int *colonnes;
	double *valeurs; 
	
	/* Déclarations des tableaux de caractères des noms de variables et de contraintes. */	
	char **nomcontr;
	char **numero;	
	char **nomvar; 

	/* Variables récupérant les résultats de la résolution du problème (fonction objectif et valeur des variables) */
	
	double z; 
	double *x; 

	/* Autres déclarations */ 

	int i, j;
	int *L, *t; // Tableau pour la fonction regroupement
	int nbregroup;
	int nbcreux; // Nombre d'éléments de la matrice creuse
	int cpt; // Compteur utilise dans le remplissage de la matrice creuse

	/* Chargement des données à partir d'un fichier */
	
	lecture_data(argv[1],&p);
	
	/* Lancement de la résolution... */

	crono_start(); // Lancement du chronomètre

	p.regroupe.longueur = NULL;
	p.regroupe.n = NULL;
	p.regroupe.tab = NULL;
	nbregroup = 0;

	L = (int *) malloc(i*sizeof(int));
	t = (int *) malloc((p.nblieux-1)*sizeof(int));

	for(j=0;j<p.nblieux-1;++j)
	{
		t[j] = j+1;
	}

	for(i=1; i<p.nblieux; ++i)
	{
		nbregroup = regroupement(&p, i, nbregroup, 0, L, t, p.nblieux-1);	
	}

	prob = glp_create_prob(); // Allocation mémoire pour le problème 
	glp_set_prob_name(prob, "BladeFlyer"); // Affectation d'un nom
	glp_set_obj_dir(prob, GLP_MIN); // Il s'agit d'un problème de minimisation
		

	glp_add_rows(prob, p.nbcontr); // Ajout du nombre de contraintes dans la matrice des contraintes
	nomcontr = (char **) malloc (p.nbcontr * sizeof(char *));
	numero = (char **) malloc (p.nbcontr * sizeof(char *)); 

	for(i=1;i<p.nblieux;++i)
	{
		/* Donner un nom aux contraintes */
		nomcontr[i - 1] = (char *) malloc (9 * sizeof(char)); // Hypothèse simplificatrice : on a au plus 16 caractères, 6 pour "Goupe" + 3 pour au moins 999 groupes
		numero[i - 1] = (char *) malloc (3  * sizeof(char)); // Même hypothèse sur la taille du problème
		strcpy(nomcontr[i-1], "Groupe");
		sprintf(numero[i-1], "%d", i);
		strcat(nomcontr[i-1], numero[i-1]); // Les contraintes sont nommés "Groupe1", "Groupe2"...		
		glp_set_row_name(prob, i, nomcontr[i-1]); // Affectation du nom à la contrainte i
		glp_set_row_bnds(prob, i, GLP_FX, 1.0, 0.0); // Ajout de la contrainte d'égalite, ici = 1
	}


	p.nbvar = nbregroup; // Declaration du nombre de variables : nombre de regroupements
	
	glp_add_cols(prob, p.nbvar); // Ajout du nombres de variables dans le problème GLPK
	nomvar = (char **) malloc (p.nbvar * sizeof(char *));

	for(i=1;i<=p.nbvar;++i)
	{
		/* Donner un nom aux variables */
		nomvar[i - 1] = (char *) malloc (10 * sizeof(char));
		sprintf(nomvar[i-1],"X%d",i);
		glp_set_col_name(prob, i, nomvar[i-1]); // Les variables sont nommées "X1", "X2"... 
		glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0); // Bornes sur les variables
		glp_set_col_kind(prob, i, GLP_BV);	// Variables binaires donc GLP_BV
		
	}

	// Définition des coefficients des variables dans la fonction objectif 
	for(i=1;i<=p.nbvar;++i)
	{
		glp_set_obj_coef(prob,i,p.regroupe.longueur[i-1]);  
	}


	nbcreux = nbregroup*(p.nblieux-1); // Au maximum, il y a n points de pompages fois le nombre de regroupements de coefficients non-nuls dans la matrice creuse
	cpt = 1; // Initialisation du premier indice

	/* Allocation de l'espace mémoire nécessaire aux lignes, aux colonnes et aux valeurs de la matrice creuse */
	lignes = (int *) malloc ((1 + nbcreux) * sizeof(int));
	colonnes = (int *) malloc ((1 + nbcreux) * sizeof(int));
	valeurs = (double *) malloc ((1 + nbcreux) * sizeof(double));
	
	for(i=0 ; i<nbregroup ; ++i) 
	{   
		for(j=0;j<p.regroupe.n[i];++j) 
		{ 
			lignes[cpt] = p.regroupe.tab[i][j];
			colonnes[cpt] = i+1;
			valeurs[cpt] = 1.0;
			cpt++;
		}
	}
	
	nbcreux = cpt-1; // Déclaration du vrai nombres de coefficients non-nuls dans la matrice creuse

	/* hargement de la matrice dans le problème */
	glp_load_matrix(prob,nbcreux,lignes,colonnes,valeurs); 
	
	/* Ecriture de la modélisation dans un fichier (utile pour debugger) */
	glp_write_lp(prob,NULL,"projet_debug.lp");

	/* Résolution */	
	glp_simplex(prob,NULL);	
	glp_intopt(prob,NULL); 

	/* Problème résolu, arrêt du chrono */
	crono_stop();
	temps = crono_ms()/1000,0;

	/* Résolution de la valeur optimale */
	z = glp_mip_obj_val(prob); 
	
	/* Affichage des résultats */
	x = (double *) malloc (p.nbvar * sizeof(double));
	for(i = 0;i < nbregroup;++i)
	{
		x[i+1] = glp_mip_col_val(prob,i+1); /* Récupération de la valeur des variables */

	}
	printf("z = %lf\n",z);

	// Arrondi
	for(i = 0;i < nbregroup;++i)
	{
		printf("x%d = %d, ",i+1,(int)(x[i+1] + 0.5));
	}
	printf("\n");
	
	printf("Temps : %f\n",temps);	
	


	/*for(i=0 ; i<nbregroup ; ++i) 
	{   
		printf("%d = {", i+1);
		fflush(stdout);
		for(j=0;j<p.regroupe.n[i];++j) 
		{ 
			printf("%d",p.regroupe.tab[i][j]);
			fflush(stdout);   
		}
		//printf("\n");
		printf(" %d ", p.regroupe.longueur[i]);
		printf("}\n ");
	}
	printf("\n");*/


	/* Libération mémoire */
	free_data(&p);
	
	return 0;
}
