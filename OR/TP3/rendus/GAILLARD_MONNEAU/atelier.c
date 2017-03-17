/*
MONNEAU Dylan && GAILLARD Florent 601A
*/

#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */
#include <math.h> /* Bibliotheque Math pour les fonctions mathématiques comme sqrt */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure contenant les données du problème */

typedef struct {
	int nbvar; // Nombre de variables
	int nbcontr; // Nombre de contraintes 
	int *couts; // Tableau des couts
	int **contr; // Matrice creuse des contraintes
	int *sizeContr; // Tableau des nombres de variables dans chacune des contraintes
	int *droite; // Tableau des valeurs des membres de droites des contraintes
} donnees;


/* lecture des donnees */

void lecture_data(char *file, donnees *p)
{

	FILE *fin; // Pointeur sur un fichier
	int i,j;	
	int val;
	
	fin = fopen(file,"r"); // Ouverture du fichier en lecture
	
	/* Première ligne du fichier, on lit le nombre de variables puis le nombre de contraintes */

	fscanf(fin,"%d",&val);
	p->nbvar = val;
	fscanf(fin,"%d",&val);
	p->nbcontr = val;
		
	/* On peut maintenant faire les allocations dynamiques dépendant du nombre de variables et du nombre de contraintes */
	
	p->couts = (int *) malloc (p->nbvar * sizeof(int));
	p->droite = (int *) malloc (p->nbcontr * sizeof(int));
	p->sizeContr = (int *) malloc (p->nbcontr * sizeof(int));
	p->contr = (int **) malloc (p->nbcontr * sizeof(int *)); // Il restera ensuite à dimensionner chaque "ligne" de la matrice creuse des contraintes
	
	/* Deuxième ligne du fichier, on lit les coefficients de la fonction objectif */
	
	for(i = 0;i < p->nbvar;i++)
	{
		fscanf(fin,"%d",&val);
		p->couts[i] = val;
	}
		
	/* On lit ensuite les contraintes du problème (par paquet de 3 lignes) */
	
	for(i = 0;i < p->nbcontr;i++) // Pour chaque contrainte,
	{
		// Lecture du nombre de variables dans la contrainte, permettant ensuite de dimensionner correctement la "ligne" correspondante
		fscanf(fin,"%d",&val);
		p->sizeContr[i] = val;
		p->contr[i] = (int *) malloc (p->sizeContr[i] * sizeof(int));
		
		// Lecture des indice des variables intervenant dans la contrainte
		for(j = 0;j < p->sizeContr[i];j++)
		{
			fscanf(fin,"%d",&val);
			p->contr[i][j] = val;
		}
		
		// Lecture du membre de droite de la contrainte
		fscanf(fin,"%d",&val);
		p->droite[i] = val; 
	}
		
	fclose(fin); // Fermeture du fichier
}


int main(int argc, char *argv[])
{	
	/* Données du problème */
	
	donnees p; 

	/* structures de données propres à GLPK */
	
	glp_prob *prob; // déclaration d'un pointeur sur le problème
	int *lignes;
	int *colonnes;
	double *valeurs; // déclaration des 3 tableaux servant à définir la matrice "creuse" des contraintes
	
	/* Les déclarations suivantes sont optionnelles, leur but est de donner des noms aux variables et aux contraintes.
	   Cela permet de lire plus facilement le modèle saisi si on en demande un affichage à GLPK, ce qui est souvent utile pour détecter une erreur! */
	
	char **nomcontr;
	char **numero;	
	char **nomvar; 

    /* variables récupérant les résultats de la résolution du problème (fonction objectif et valeur des variables) */
	
	double z; 
	double *x; 
	
	/* autres déclarations */ 
	
	int i,j;
	int nbcreux; // nombre d'éléments de la matrice creuse
	int pos; // compteur utilisé dans le remplissage de la matrice creuse
		
	/* Chargement des données à partir d'un fichier */
	
	lecture_data(argv[1],&p); // argv[1] : nom du fichier de données
	
	/* Transfert de ces données dans les structures utilisées par la bibliothèque GLPK */
	
	prob = glp_create_prob(); /* allocation mémoire pour le problème */ 
	glp_set_prob_name(prob, "atelier"); /* affectation du nom atelier au probleme */
	glp_set_obj_dir(prob, GLP_MAX); /* Il s'agit d'un problème de maximisation */
	
	/* Déclaration du nombre de contraintes (nombre de lignes de la matrice des contraintes) : p.nbcontr */
	
	glp_add_rows(prob, p.nbcontr); 
	nomcontr = (char **) malloc (p.nbcontr * sizeof(char *));
	numero = (char **) malloc (p.nbcontr * sizeof(char *)); 

	/* On commence par préciser les bornes sur les constrainte, les indices commencent à 1 (!) dans GLPK */

	for(i=1;i<=p.nbcontr;i++)
	{
		/* On donne un nom aux contraintes */
		nomcontr[i - 1] = (char *) malloc (8 * sizeof(char));
		numero[i - 1] = (char *) malloc (3  * sizeof(char));
		// la première moitié des contraintes seront nommées personne1, personne2 ... 
		if(i<=p.nbcontr/2) {
			strcpy(nomcontr[i-1], "personne");
			sprintf(numero[i-1], "%d", i);
		}
		// l'autre moitié des contraintes seront nommées machine1, machine2 ...  
		else {
			strcpy(nomcontr[i-1], "machine");
			sprintf(numero[i-1], "%d", (i-p.nbcontr/2));
		}

		strcat(nomcontr[i-1], numero[i-1]); /* Ajout du numéro au nom */					
		glp_set_row_name(prob, i, nomcontr[i-1]); /* Affectation du nom à la contrainte i */
		
		/* égalité (GLP_FX) sur les contraintes en l'occurence p.droite[i-1] */
		glp_set_row_bnds(prob, i, GLP_FX, p.droite[i-1], 1.0); 
	}	

	/* Déclaration du nombre de variables : p.nbvar */
	glp_add_cols(prob, p.nbvar); 
	nomvar = (char **) malloc (p.nbvar * sizeof(char *)); // allocation mémoire pour le nom des variables
	
	char **numeroi = (char **) malloc (p.nbvar * sizeof(char *)); 
	char **numeroj = (char **) malloc (p.nbvar * sizeof(char *)); 
	int indice; // calcul de l'indice de 1 à 36
	for(i=1;i<=sqrt(p.nbvar);i++)
	{
		for(j=1;j<=sqrt(p.nbvar);j++)
		{
			indice = (i-1)*sqrt(p.nbvar)+j;
			nomvar[indice] = (char *) malloc (5 * sizeof(char));
			numeroi[indice] = (char *) malloc (3  * sizeof(char)); 
			numeroj[indice] = (char *) malloc (3  * sizeof(char));

			sprintf(numeroi[indice], "%d", i);
			sprintf(numeroj[indice], "%d", j);

			strcpy(nomvar[indice],"x");
			strcat(nomvar[indice],numeroi[indice]); // nomvar[indice] contient xi
			strcat(nomvar[indice],","); // nomvar[indice] contient xi,
			strcat(nomvar[indice],numeroj[indice]); // nomvar[indice] contient xi,j
			glp_set_col_name(prob, indice , nomvar[indice]); // Les variables sont nommées "x1,1", "x1,2"... afin de respecter les noms de variables de l'exercice 2.2

			glp_set_col_bnds(prob, indice, GLP_DB, 0.0, 1.0); // bornes sur les variables de 0 à 1
			glp_set_col_kind(prob, indice, GLP_BV);	// les variables sont binaires 
		}
	}

	/* définition des coefficients des variables dans la fonction objectif */
	for(i = 1;i <= p.nbvar;i++) {
		glp_set_obj_coef(prob,i, p.couts[i-1]);  
	}
	/* Définition des coefficients non-nuls dans la matrice des contraintes, autrement dit les coefficients de la matrice creuse */
	/* Les indices commencent également à 1 ! */

	nbcreux = 0;
	for(i = 0;i < p.nbcontr;i++) nbcreux += p.sizeContr[i];
	
	lignes = (int *) malloc ((1 + nbcreux) * sizeof(int));
	colonnes = (int *) malloc ((1 + nbcreux) * sizeof(int));
	valeurs = (double *) malloc ((1 + nbcreux) * sizeof(double));
	
	pos = 1;
	for(i = 0;i < p.nbcontr;i++)
	{
		for(j = 0;j < p.sizeContr[i];j++)
		{
			lignes[pos] = i + 1;
			colonnes[pos] = p.contr[i][j];
			valeurs[pos] = 1.0; 
			pos++;
		}
	}
	
	/* chargement de la matrice dans le problème */
	
	glp_load_matrix(prob,nbcreux,lignes,colonnes,valeurs); 
	// Création du modèle dans le fichier atelier.lp
	glp_write_lp(prob,NULL,"atelier.lp");

	/* Résolution du problème */
	
	glp_simplex(prob,NULL);	glp_intopt(prob,NULL); /* Résolution */
	z = glp_mip_obj_val(prob); /* Récupération de la valeur optimale. */
	x = (double *) malloc (p.nbvar * sizeof(double));
	for(i = 0;i < p.nbvar; i++) x[i] = glp_mip_col_val(prob,i+1); /* Récupération de la valeur des variables.*/

	// Affichage du résultats et des variables 
	printf("z = %lf\n",z);
	for(i = 1;i <= sqrt(p.nbvar);i++) {
		for(j=1; j <= sqrt(p.nbvar);j++) {
			indice = (i-1)* sqrt(p.nbvar) + j;
			// Affichage de la valeur de x si égale à 1
			if(x[indice-1]==1) {
				printf("%s = %d\n",nomvar[indice],(int)(x[indice-1] + 0.5));
			}
		}
	}
	/* libération mémoire */
	glp_delete_prob(prob); 
	free(p.couts);
	free(p.sizeContr);
	free(p.droite);
	for(i = 0;i < p.nbcontr;i++) free(p.contr[i]);
	free(p.contr);

	return 0;
}
