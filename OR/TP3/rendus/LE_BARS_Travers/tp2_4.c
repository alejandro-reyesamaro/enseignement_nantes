/* Yannis Le Bars - Clément Travers */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

/* Structure contenant les données du problème */

typedef struct {
	int nbvar; // Nombre de variables
	int nbmp; // Nombres de machines/personnes
	int nbcontr; // Nombre de contraintes 
	int **productivite; // Tableau de la productivité
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
	p->nbmp = val;


	/* Déclaration du nombre de variables : p.nbvar */
	p->nbvar = p->nbmp * p->nbmp;

	/* Déclaration du nombre de contraintes (nombre de lignes de la matrice des contraintes) : p.nbcontr */
	p->nbcontr = p->nbmp *2;
		
	/* On peut maintenant faire les allocations dynamiques dépendant du nombre de variables et du nombre de contraintes */

	p->productivite = (int **) malloc (p->nbmp * sizeof(int *)); 
	
	/* Deuxième ligne du fichier, on lit les coefficients de la fonction objectif */
	
	for(i = 0;i < p->nbmp;++i)
	{
		/* On alloue l'espace mémoire nécessaire pour le nombre de machines */
		p->productivite[i] = (int *) malloc (p->nbmp * sizeof(int));
		for(j = 0; j < p->nbmp;++j)
		{
			fscanf(fin,"%d",&val);
			p->productivite[i][j] = val;
		}
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
	
	int i, j;
	int nbcreux; // nombre d'éléments de la matrice creuse
	int pos; // compteur utilisé dans le remplissage de la matrice creuse

	/* Chargement des données à partir d'un fichier */
	
	lecture_data(argv[1],&p);
	
	/* Transfert de ces données dans les structures utilisées par la bibliothèque GLPK */
	
	prob = glp_create_prob(); /* allocation mémoire pour le problème */ 
	glp_set_prob_name(prob, "Atelier"); /* affectation d'un nom (on pourrait mettre NULL) */
	glp_set_obj_dir(prob, GLP_MAX); /* Il s'agit d'un problème de minimisation, on utiliserait la constante GLP_MAX dans le cas contraire */
	


	glp_add_rows(prob, p.nbcontr); 
	nomcontr = (char **) malloc (p.nbcontr * sizeof(char *));
	numero = (char **) malloc (p.nbcontr * sizeof(char *)); 

	/* On commence par préciser les bornes sur les constrainte, les indices commencent à 1 (!) dans GLPK */
	for(i=1;i<=p.nbmp;++i)
	{
		/* partie optionnelle : donner un nom aux contraintes */
		nomcontr[i - 1] = (char *) malloc (10 * sizeof(char)); // hypothèse simplificatrice : on a au plus 7 caractères, sinon il faudrait dimensionner plus large! 
		numero[i - 1] = (char *) malloc (2  * sizeof(char)); // Même hypothèse sur la taille du problème
		strcpy(nomcontr[i-1], "personne");
		sprintf(numero[i-1], "%d", i);
		strcat(nomcontr[i-1], numero[i-1]); /* Les contraintes sont nommés "personne1", "personne2"... */		
		glp_set_row_name(prob, i, nomcontr[i-1]); /* Affectation du nom à la contrainte i */
		
		/* partie indispensable : les bornes sur les contraintes */
		glp_set_row_bnds(prob, i, GLP_FX, 1.0, 0.0); 
	}
	
	for(i=1;i<=p.nbmp;++i)
	{
		/* partie optionnelle : donner un nom aux contraintes */
		nomcontr[p.nbmp - 1 + i] = (char *) malloc (9 * sizeof(char)); // hypothèse simplificatrice : on a au plus 7 caractères, sinon il faudrait dimensionner plus large! 
		numero[p.nbmp - 1 + i] = (char *) malloc (2  * sizeof(char)); // Même hypothèse sur la taille du problème
		strcpy(nomcontr[p.nbmp - 1 + i], "machine");
		sprintf(numero[p.nbmp - 1 + i], "%d", i);
		strcat(nomcontr[p.nbmp - 1 + i], numero[p.nbmp - 1 + i]); /* Les contraintes sont nommés "machine1", "machine2"... */		
		glp_set_row_name(prob, p.nbmp + i, nomcontr[p.nbmp - 1 + i]); /* Affectation du nom à la contrainte i */
		
		/* partie indispensable : les bornes sur les contraintes */
		glp_set_row_bnds(prob, p.nbmp + i, GLP_FX, 1.0, 0.0); 
	}


	glp_add_cols(prob, p.nbvar); 
	nomvar = (char **) malloc (p.nbvar * sizeof(char *));
	
	/* On précise le type des variables, les indices commencent à 1 également pour les variables! */
	
	for(i=1;i<=p.nbmp;++i)
	{
		for(j=1;j<=p.nbmp;++j)
		{
			/* partie optionnelle : donner un nom aux variables */
			nomvar[i - 1] = (char *) malloc (3 * sizeof(char));
			sprintf(nomvar[i-1],"X%d%d",i,j);
			glp_set_col_name(prob, (i-1)*p.nbmp+j , nomvar[i-1]); /* Les variables sont nommées "X11", "X12"... afin de respecter les noms de variables de l'exercice 2.4 */

			/* partie obligatoire : bornes éventuelles sur les variables, et type */
			glp_set_col_bnds(prob, (i-1)*p.nbmp+j, GLP_DB, 0.0, 1.0); /* bornes sur les variables, comme sur les contraintes */
			glp_set_col_kind(prob, (i-1)*p.nbmp+j, GLP_BV);	/* les variables sont par défaut continues, nous précisons ici qu'elles sont binaires avec la constante GLP_BV, on utiliserait GLP_IV pour des variables entières */	
		}
	} 

	/* définition des coefficients des variables dans la fonction objectif */

	for(i = 1;i <= p.nbmp;++i) 
	{
		for(j = 1;j <= p.nbmp;++j)
		{
			glp_set_obj_coef(prob,(i-1)*p.nbmp+j,p.productivite[i - 1][j - 1]);  
		}
	}
	
	/* Définition des coefficients non-nuls dans la matrice des contraintes, autrement dit les coefficients de la matrice creuse */
	/* Les indices commencent également à 1 ! */

	nbcreux = p.nbmp*p.nbmp*2;
	
	/* Allocation de l'espace mémoire nécessaire aux lignes, aux colonnes et aux valeurs de la matrice creuse */
	lignes = (int *) malloc ((1 + nbcreux) * sizeof(int));
	colonnes = (int *) malloc ((1 + nbcreux) * sizeof(int));
	valeurs = (double *) malloc ((1 + nbcreux) * sizeof(double));
	
	pos = 1;
	// Toute personne est affectee a une et une seule machine
	for(i = 0;i < p.nbmp;i++)
	{
		for(j = 0;j < p.nbmp;j++)
		{

			lignes[pos] =  i + 1;
			colonnes[pos] = i*p.nbmp+j + 1;
			valeurs[pos] = 1.0;
			pos++;
		}
	}

	// Toute machine est affectee a une et une seule personne
	for(j = 0;j < p.nbmp;j++)
	{
		for(i = 0;i < p.nbmp;i++)
		{
			lignes[pos] = p.nbmp + j + 1;
			colonnes[pos] = i*p.nbmp+ j + 1;
			valeurs[pos] = 1.0;
			pos++;
		}
	}

	/* chargement de la matrice dans le problème */
	
	glp_load_matrix(prob,nbcreux,lignes,colonnes,valeurs); 
	
	/* Optionnel : écriture de la modélisation dans un fichier (utile pour debugger) */

	glp_write_lp(prob,NULL,"atelier_debug.lp");

	/* Résolution, puis lecture des résultats */
	
	glp_simplex(prob,NULL);	
	glp_intopt(prob,NULL); 
	/* Résolution */

	z = glp_mip_obj_val(prob); 
	/* Récupération de la valeur optimale */
	
	x = (double *) malloc (p.nbvar * sizeof(double));
	for(i = 0;i < p.nbmp;i++)
	{
		for(j = 0;j < p.nbmp;j++)
		{
			x[i*p.nbmp+j+1] = glp_mip_col_val(prob,i*p.nbmp+j+1); /* Récupération de la valeur des variables */
		}
	}
	printf("z = %lf\n",z);

	// Arrondi
	for(i = 0;i < p.nbmp;i++)
	{
		for(j = 0;j < p.nbmp;j++)
		{
			printf("x%d,%d = %d, ",i+1,j+1,(int)(x[i*p.nbmp+j+1] + 0.5));
		}
	}

	puts("");

	/* libération mémoire */
	glp_delete_prob(prob); 
	for(i = 0;i < p.nbmp;i++) free(p.productivite[i]);
	free(p.productivite);

	return 0;
}
