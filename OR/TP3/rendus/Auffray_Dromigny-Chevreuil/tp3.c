/* Exercice TP 3 - Utilisation de GLPK en tant que bibliothèque de fonctions */
/* Par Baptiste Auffray et Ivan Dromigny--Chevreuil */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h>

/* Structure contenant les données du problème */


typedef struct {
	int nbH; 			// Nombre d'homme
	int nbM;			// Nombre de machine
	int nbContr; 		// Nombre de contraintes 
	int *prod; 			// Tableau des productivitées (coefficiant de la fonction objectif)
} donnees;


/* Définitiob du type boolean */

typedef int bool;
#define true 1
#define false 0


/* Lecture des donnees */

void lecture_data(char *file, donnees *p)
{

	FILE *fin; // Pointeur sur un fichier
	int i,j;
	int val;
	
	fin = fopen(file,"r"); // Ouverture du fichier en lecture


	/* Première ligne du fichier, on lit le nombre de variables (nombre d'hommes puis nombre de machines) puis le nombre de contraintes */

	fscanf(fin,"%d",&val);
	p->nbH = val;
	fscanf(fin,"%d",&val);
	p->nbM = val;
	fscanf(fin,"%d",&val);
	p->nbContr = val;
		
	/* On peut maintenant faire les allocations dynamiques dépendant du nombre de variables et du nombre de contraintes */
	
	p->prod = (int *) malloc (p->nbH*p->nbM * sizeof(int));

	/* On lit les coefficients de la fonction objectif */
	
	for(i = 0;i < p->nbH*p->nbM;i++){
		fscanf(fin,"%d",&val);
		p->prod[i] = val;
	}
		
	fclose(fin); // Fermeture du fichier
}


int main(int argc, char *argv[])
{	
	/* Données du problème */
	
	donnees data; 

	/* Structures de données propres à GLPK */
	
	glp_prob *prob; // Déclaration d'un pointeur sur le problème

	// Déclaration des 3 tableaux servant à définir la matrice "creuse" des contraintes
	int *lignes;
	int *colonnes;
	double *valeurs; 
	

	/* Les déclarations suivantes sont optionnelles, leur but est de donner des noms aux variables et aux contraintes. */
	
	char **nomContr;
	char **numeroC;	
	char **numeroV;
	char **nomVar; 


    /* Variables récupérant les résultats de la résolution du problème (fonction objectif et valeur des variables) */
	
	int z; 
	bool *x; 


	/* Autres déclarations */ 
	
	int i,j;
	int nbCreux; // Nombre d'éléments de la matrice creuse
	int pos;	 // Compteur utilisé pour le remplissage de la matrice creuse
		

	/* Chargement des données à partir d'un fichier */
	
	lecture_data(argv[1],&data);


	/* Transfert de ces données dans les structures utilisées par la bibliothèque GLPK */
	
	prob = glp_create_prob(); 				// Allocation mémoire pour le problème
	glp_set_prob_name(prob, "machines"); 	// Affectation d'un nom
	glp_set_obj_dir(prob, GLP_MAX);
	

	/* Déclaration du nombre de contraintes (nombre de lignes de la matrice des contraintes) : data.nbContr */
	
	glp_add_rows(prob, data.nbContr); 
	nomContr = (char **) malloc (data.nbContr * sizeof(char *));
	numeroC = (char **) malloc (data.nbContr * sizeof(char *)); 


	/* On commence par préciser les bornes sur les constrainte, les indices commencent à 1 (!) dans GLPK */

	for(i = 1; i <= data.nbContr; i++){

		/* Partie optionnelle : donner un nom aux contraintes */

		nomContr[i - 1] = (char *) malloc (16 * sizeof(char)); 
		numeroC[i - 1] = (char *) malloc (3  * sizeof(char)); 	// Même hypothèse sur la taille du problème
		strcpy(nomContr[i-1], "Contrainte ");
		sprintf(numeroC[i-1], "%d", i);
		strcat(nomContr[i-1], numeroC[i-1]); 	
		glp_set_row_name(prob, i, nomContr[i-1]); // Affectation du nom à la contrainte i
		

		/* Partie indispensable : les bornes sur les contraintes */

		glp_set_row_bnds(prob, i, GLP_FX, 1.0, 0.0); // La borne est égale à 1.0 pour toutes les contraintes
	}	


	/* Déclaration du nombre de variables : data.nbH * data.nbM */
	
	glp_add_cols(prob, data.nbH*data.nbM); 
	nomVar = (char **) malloc (data.nbH * data.nbM * sizeof(char *));
	numeroV = (char **) malloc (data.nbH * data.nbM * sizeof(char *)); 
	

	/* On précise le type des variables, les indices commencent à 1 également pour les variables! */
	
	for(i = 1; i <= data.nbH*data.nbM; i++){

		/* Partie optionnelle : donner un nom aux variables */

		nomVar[i - 1] = (char *) malloc (3 * sizeof(char));
		numeroV[i - 1] = (char *) malloc (3  * sizeof(char));
		strcpy(nomVar[i-1], "x");
		sprintf(numeroV[i-1], "%d", i);
		strcat(nomVar[i-1], numeroV[i-1]); 	
		glp_set_col_name(prob, i , nomVar[i-1]);

		/* Partie obligatoire : bornes sur les variables */

		glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0);
		glp_set_col_kind(prob, i, GLP_BV);
	} 

	/* Définition des coefficients des variables dans la fonction objectif */

	for(i = 1; i <= data.nbH * data.nbM; i++) glp_set_obj_coef(prob,i,data.prod[i - 1]);  
	
	/* Définition des coefficients non-nuls dans la matrice creuse */

	nbCreux = 0;
	for(i = 0; i < data.nbContr; i++) nbCreux += data.nbM;
	
	lignes = (int *) malloc ((1 + nbCreux) * sizeof(int));
	colonnes = (int *) malloc ((1 + nbCreux) * sizeof(int));
	valeurs = (double *) malloc ((1 + nbCreux) * sizeof(double));
	
	pos = 1;
	for(i = 0; i < data.nbContr; i++){
		for(j = 0; j < data.nbM; j++){
			if (i < data.nbM){
				lignes[pos] = i + 1;
				colonnes[pos] = j+1 + i*data.nbH;
				valeurs[pos] = 1.0;
			}
			else {
				lignes[pos] = i + 1;
				colonnes[pos] = (i % 6)+1 + j*data.nbM;
				valeurs[pos] = 1.0;
			}
			pos++;
		}
	}

	
	/* Chargement de la matrice dans le problème */
	
	glp_load_matrix(prob,nbCreux,lignes,colonnes,valeurs); 
	

	/* Optionnel : écriture de la modélisation dans un fichier (utile pour debugger) */

	glp_write_lp(prob,NULL,"machine.lp");


	/* Résolution, puis lecture des résultats */
	
	glp_simplex(prob,NULL);	glp_intopt(prob,NULL); 	// Résolution 
	z = glp_mip_obj_val(prob);						// Récupération de la valeur optimale
	x = (bool *) malloc (data.nbH*data.nbM * sizeof(bool));
	for(i = 0; i < data.nbH*data.nbM; i++) x[i] = glp_mip_col_val(prob,i+1); // Récupération de la valeur des variables

	printf("z = %d\n",z);
	for(i = 0; i < data.nbH*data.nbM; i++) printf("x%c = %d, ",i,(int)(x[i]));

	/* Libération mémoire */
	glp_delete_prob(prob); 
	free(data.prod);


	return 0;
}