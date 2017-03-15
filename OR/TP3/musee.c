/* Utilisation de GLPK en mode bibliothèque */
/* Il s'agit de l'exercice 2.2 des feuilles de TD, qui a servi à illustrer l'utilisation d'une matrice creuse avec GNUMathProg */
/* Ici, toutes les données sont saisies "en dur" dans le code, et nous nous permettons donc des allocations statiques. 
   En cas de lecture des données dans un fichier, des allocations dynamiques seraient nécessaires. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

#define NBVAR 17
#define NBCONTR 10
#define NBCREUX 33


int main(int argc, char *argv[])
{	
	/* structures de données propres à GLPK */
	
	glp_prob *prob; // déclaration d'un pointeur sur le problème
	int ia[1 + NBCREUX];
	int ja[1 + NBCREUX];
	double ar[1 + NBCREUX]; // déclaration des 3 tableaux servant à définir la partie creuse de la matrice des contraintes

	/* variables récupérant les résultats de la résolution du problème (fonction objectif et valeur des variables) */

	int i;
	double z; 
	double x[NBVAR]; 
	
	/* Les déclarations suivantes sont optionnelles, leur but est de donner des noms aux variables et aux contraintes.
	   Cela permet de lire plus facilement le modèle saisi si on en demande un affichage à GLPK, ce qui est souvent utile pour détecter une erreur! */
	
	char nomcontr[NBCONTR][8]; /* ici, les contraintes seront nommées "salle1", "salle2",... */
	char numero[NBCONTR][3]; /* pour un nombre à deux chiffres */	
	char nomvar[NBVAR][3]; /* "xA", "xB", ... */
	
	/* Création d'un problème (initialement vide) */
	
	prob = glp_create_prob(); /* allocation mémoire pour le problème */ 
	glp_set_prob_name(prob, "musee"); /* affectation d'un nom (on pourrait mettre NULL) */
	glp_set_obj_dir(prob, GLP_MIN); /* Il s'agit d'un problème de minimisation, on utiliserait la constante GLP_MAX dans le cas contraire */
	
	/* Déclaration du nombre de contraintes (nombre de lignes de la matrice des contraintes) : NBCONTR */
	
	glp_add_rows(prob, NBCONTR); 

	/* On commence par préciser les bornes sur les constrainte, les indices des contraintes commencent à 1 (!) dans GLPK */

	for(i = 1;i <= NBCONTR;i++)
	{
		/* partie optionnelle : donner un nom aux contraintes */
		strcpy(nomcontr[i-1], "salle");
		sprintf(numero[i-1], "%d", i);
		strcat(nomcontr[i-1], numero[i-1]); /* Les contraintes sont nommés "salle1", "salle2"... */		
		glp_set_row_name(prob, i, nomcontr[i-1]); /* Affectation du nom à la contrainte i */
		
		/* partie indispensable : les bornes sur les contraintes */
		if (i == 4) glp_set_row_bnds(prob, i, GLP_LO, 2.0, 0.0);
		else glp_set_row_bnds(prob, i, GLP_LO, 1.0, 0.0);
		/* Avec GLPK, on peut définir simultanément deux contraintes, si par exemple, on a pour une contrainte i : "\sum x_i >= 0" et "\sum x_i <= 5",
		   on écrit alors : glp_set_row_bnds(prob, i, GLP_DB, 0.0, 5.0); la constante GLP_DB signifie qu'il y a deux bornes sur "\sum x_i" qui sont ensuite données.
		   Ici, nous n'avons qu'une seule contrainte du type "\sum x_i >= 1" (ou "\sum x_i >= 2" pour la contrainte 4) soit une borne inférieure sur "\sum x_i", on écrit donc glp_set_row_bnds(prob, i, GLP_LO, 1.0, 0.0); le paramètre "0.0" est ignoré. 
		   Les autres constantes sont GLP_UP (borne supérieure sur le membre de gauche de la contrainte) et GLP_FX (contrainte d'égalité).   
		 Remarque : les membres de gauches des contraintes "\sum x_i ne sont pas encore saisis, les variables n'étant pas encore déclarées dans GLPK */ 
	}	

	/* Déclaration du nombre de variables : NBVAR */
	
	glp_add_cols(prob, NBVAR); 
	
	/* On précise le type des variables, les indices commencent à 1 également pour les variables! */
	
	for(i = 1;i <= NBVAR;i++)
	{
		/* partie optionnelle : donner un nom aux variables */
		sprintf(nomvar[i-1],"x%c",'B'+i-1);
		glp_set_col_name(prob, i , nomvar[i-1]); /* Les variables sont nommées "xA", "xB"... afin de respecter les noms de variables de l'exercice 2.2 */
		
		/* partie obligatoire : bornes éventuelles sur les variables, et type */
		glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0); /* bornes sur les variables, comme sur les contraintes */
		glp_set_col_kind(prob, i, GLP_BV);	/* les variables sont par défaut continues, nous précisons ici qu'elles sont binaires avec la constante GLP_BV, on utiliserait GLP_IV pour des variables entières */	
	} 

	/* définition des coefficients des variables dans la fonction objectif */

	for(i = 1;i <= NBVAR;i++) glp_set_obj_coef(prob,i,1.0); // Tous les coûts sont ici à 1! 
	
	/* Définition des coefficients non-nuls dans la matrice des contraintes, autrement dit les coefficients de la matrice creuse */
	/* Les indices commencent également à 1 ! */

	/* Contrainte Salle 1 */
	ia[1] = 1;ja[1] = 1;ar[1] = 1.0; // à la position (1,1) de la matrice des contraintes, on a un 1.0 (correspondant à 1.0 * x_B) 
	ia[2] = 1;ja[2] = 4;ar[2] = 1.0; // à la position (1,4) de la matrice des contraintes, on a un 1.0 (correspondant à 1.0 * x_E)
	ia[3] = 1;ja[3] = 5;ar[3] = 1.0; // à la position (1,1) de la matrice des contraintes, on a un 1.0 (correspondant à 1.0 * x_F)

	/* Contrainte Salle 2 */
	ia[4] = 2;ja[4] = 1;ar[4] = 1.0; // à la position (2,1) de la matrice des contraintes, on a un 1.0 (correspondant à 1.0 * x_B)
	ia[5] = 2;ja[5] = 2;ar[5] = 1.0; // à la position (2,1) de la matrice des contraintes, on a un 1.0 (correspondant à 1.0 * x_C)
	ia[6] = 2;ja[6] = 3;ar[6] = 1.0; // à la position (2,1) de la matrice des contraintes, on a un 1.0 (correspondant à 1.0 * x_D)

	/* Contrainte Salle 3 */
	ia[7] = 3;ja[7] = 3;ar[7] = 1.0; // ...
	ia[8] = 3;ja[8] = 7;ar[8] = 1.0;
	ia[9] = 3;ja[9] = 8;ar[9] = 1.0;
	
	/* Contrainte Salle 4 */
	ia[10] = 4;ja[10] = 4;ar[10] = 1.0;
	ia[11] = 4;ja[11] = 6;ar[11] = 1.0;
	ia[12] = 4;ja[12] = 11;ar[12] = 1.0;
	ia[13] = 4;ja[13] = 12;ar[13] = 1.0;

	/* Contrainte Salle 5 */
	ia[14] = 5;ja[14] = 2;ar[14] = 1.0;	
	ia[15] = 5;ja[15] = 5;ar[15] = 1.0;	
	ia[16] = 5;ja[16] = 6;ar[16] = 1.0;
	ia[17] = 5;ja[17] = 7;ar[17] = 1.0;
	ia[18] = 5;ja[18] = 9;ar[18] = 1.0;
	
	/* Contrainte Salle 6 */
	ia[19] = 6;ja[19] = 8;ar[19] = 1.0;		
	ia[20] = 6;ja[20] = 9;ar[20] = 1.0;
	ia[21] = 6;ja[21] = 15;ar[21] = 1.0;
	
	/* Contrainte Salle 7 */
	ia[22] = 7;ja[22] = 12;ar[22] = 1.0;		
	ia[23] = 7;ja[23] = 13;ar[23] = 1.0;
	
	/* Contrainte Salle 8 */
	ia[24] = 8;ja[24] = 10;ar[24] = 1.0;		
	ia[25] = 8;ja[25] = 11;ar[25] = 1.0;	
	ia[26] = 8;ja[26] = 13;ar[26] = 1.0;
	ia[27] = 8;ja[27] = 14;ar[27] = 1.0;
	ia[28] = 8;ja[28] = 17;ar[28] = 1.0;
	
	/* Contrainte Salle 9 */
	ia[29] = 9;ja[29] = 14;ar[29] = 1.0;	
	ia[30] = 9;ja[30] = 15;ar[30] = 1.0;
	ia[31] = 9;ja[31] = 16;ar[31] = 1.0;
	
	/* Contrainte Salle 10 */
	ia[32] = 10;ja[32] = 16;ar[32] = 1.0;	
	ia[33] = 10;ja[33] = 17;ar[33] = 1.0;
	
	
	/* chargement de la matrice dans le problème */ 
	
	glp_load_matrix(prob,NBCREUX,ia,ja,ar); 
	
	/* Optionnel : écriture de la modélisation dans un fichier (TRES utile pour debugger!) */

	glp_write_lp(prob,NULL,"musee.lp");

	/* Résolution, puis lecture des résultats */
	
	glp_simplex(prob,NULL);	glp_intopt(prob,NULL); /* Résolution */
	z = glp_mip_obj_val(prob); /* Récupération de la valeur optimale. Dans le cas d'un problème en variables continues, l'appel est différent : z = glp_get_obj_val(prob); */
	for(i = 0;i < NBVAR; i++) x[i] = glp_mip_col_val(prob,i+1); /* Récupération de la valeur des variables, Appel différent dans le cas d'un problème en variables continues : for(i = 0;i < p.nbvar;i++) x[i] = glp_get_col_prim(prob,i+1); */

	printf("z = %lf\n",z);
	for(i = 0;i < NBVAR;i++) printf("x%c = %d, ",'B'+i,(int)(x[i] + 0.5)); /* un cast est ajouté, x[i] pourrait être égal à 0.99999... */ 
	puts("");

	/* libération mémoire */
	glp_delete_prob(prob); 

	/* J'adore qu'un plan se déroule sans accroc! */
	return 0;
}
