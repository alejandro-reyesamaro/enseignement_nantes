/* Utilisation de GLPK en mode bibliothèque */
/* Il s'agit de l'exercice 2.2 des feuilles de TD, qui a servi à illustrer l'utilisation d'une matrice creuse avec GNUMathProg */
/* Ici, toutes les données sont saisies "en dur" dans le code, et nous nous permettons donc des allocations statiques. 
   En cas de lecture des données dans un fichier, des allocations dynamiques seraient nécessaires. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

#define NBVAR 17 // Nombre de variables
#define NBCONTR 10 // Nombre de contraintes
#define NBCREUX 34 // Nombre d'éléments de la matrice creuse (c'est-à-dire les éléments de la partie non-creuse


int main(int argc, char *argv[])
{	
	/* structures de données propres à GLPK */
	
	glp_prob *prob; // déclaration d'un pointeur sur le problème
	int ligne[1 + NBCREUX];
	int colonne[1 + NBCREUX];
	double coeff[1 + NBCREUX]; // déclaration des 3 tableaux servant à définir la partie creuse de la matrice des contraintes

	/* variables récupérant les résultats de la résolution du problème (fonction objectif et valeur des variables) */

	int i;
	double z; 
	double x[NBVAR]; 
	
	/* Les déclarations suivantes sont optionnelles, leur but est de donner des noms aux variables et aux contraintes.
	   Cela permet de lire plus facilement le modèle saisi si on en demande un affichage à GLPK, ce qui est souvent utile pour détecter une erreur! */
	
	char nomcontr[NBCONTR][8]; /* ici, les contraintes seront nommées "salle1", "salle2",... */
	char numero[NBCONTR][3]; /* pour un nombre à deux chiffres */	
	char nomvcoeff[NBVAR][3]; /* "xA", "xB", ... */
	
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
		sprintf(nomvcoeff[i-1],"x%c",'B'+i-1);
		glp_set_col_name(prob, i , nomvcoeff[i-1]); /* Les variables sont nommées "xA", "xB"... afin de respecter les noms de variables de l'exercice 2.2 */
		
		/* partie obligatoire : bornes éventuelles sur les variables, et type */
		glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0); /* bornes sur les variables, comme sur les contraintes */
		glp_set_col_kind(prob, i, GLP_BV);	/* les variables sont par défaut continues, nous précisons ici qu'elles sont binaires avec la constante GLP_BV, on utiliserait GLP_IV pour des variables entières */	
	} 

	/* définition des coefficients des variables dans la fonction objectif */

	for(i = 1;i <= NBVAR;i++) glp_set_obj_coef(prob,i,1.0); // Tous les coûts sont ici à 1! 
	
	/* Définition des coefficients non-nuls dans la matrice des contraintes, autrement dit les coefficients de la matrice creuse */
	/* Les indices commencent également à 1 ! */

	/* Contrainte Salle 1 */
	ligne[1] = 1;colonne[1] = 1;coeff[1] = 1.0; // à la position (1,1) de la matrice des contraintes, on a un 1.0 (correspondant à 1.0 * x_B) 
	ligne[2] = 1;colonne[2] = 4;coeff[2] = 1.0; // à la position (1,4) de la matrice des contraintes, on a un 1.0 (correspondant à 1.0 * x_E)
	ligne[3] = 1;colonne[3] = 5;coeff[3] = 1.0; // à la position (1,5) de la matrice des contraintes, on a un 1.0 (correspondant à 1.0 * x_F)

	/* Contrainte Salle 2 */
	ligne[4] = 2;colonne[4] = 1;coeff[4] = 1.0; // à la position (2,1) de la matrice des contraintes, on a un 1.0 (correspondant à 1.0 * x_B)
	ligne[5] = 2;colonne[5] = 2;coeff[5] = 1.0; // à la position (2,2) de la matrice des contraintes, on a un 1.0 (correspondant à 1.0 * x_C)
	ligne[6] = 2;colonne[6] = 3;coeff[6] = 1.0; // à la position (2,3) de la matrice des contraintes, on a un 1.0 (correspondant à 1.0 * x_D)

	/* Contrainte Salle 3 */
	ligne[7] = 3;colonne[7] = 3;coeff[7] = 1.0; // ...
	ligne[8] = 3;colonne[8] = 7;coeff[8] = 1.0;
	ligne[9] = 3;colonne[9] = 8;coeff[9] = 1.0;
	
	/* Contrainte Salle 4 */
	ligne[10] = 4;colonne[10] = 4;coeff[10] = 1.0;
	ligne[11] = 4;colonne[11] = 6;coeff[11] = 1.0;
	ligne[12] = 4;colonne[12] = 11;coeff[12] = 1.0;
	ligne[13] = 4;colonne[13] = 12;coeff[13] = 1.0;

	/* Contrainte Salle 5 */
	ligne[14] = 5;colonne[14] = 2;coeff[14] = 1.0;	
	ligne[15] = 5;colonne[15] = 5;coeff[15] = 1.0;	
	ligne[16] = 5;colonne[16] = 6;coeff[16] = 1.0;
	ligne[17] = 5;colonne[17] = 7;coeff[17] = 1.0;
	ligne[18] = 5;colonne[18] = 9;coeff[18] = 1.0;
	ligne[19] = 5;colonne[19] = 10;coeff[19] = 1.0;
	
	/* Contrainte Salle 6 */
	ligne[20] = 6;colonne[20] = 8;coeff[20] = 1.0;		
	ligne[21] = 6;colonne[21] = 9;coeff[21] = 1.0;
	ligne[22] = 6;colonne[22] = 15;coeff[22] = 1.0;
	
	/* Contrainte Salle 7 */
	ligne[23] = 7;colonne[23] = 12;coeff[23] = 1.0;		
	ligne[24] = 7;colonne[24] = 13;coeff[24] = 1.0;
	
	/* Contrainte Salle 8 */
	ligne[25] = 8;colonne[25] = 10;coeff[25] = 1.0;		
	ligne[26] = 8;colonne[26] = 11;coeff[26] = 1.0;	
	ligne[27] = 8;colonne[27] = 13;coeff[27] = 1.0;
	ligne[28] = 8;colonne[28] = 14;coeff[28] = 1.0;
	ligne[29] = 8;colonne[29] = 17;coeff[29] = 1.0;
	
	/* Contrainte Salle 9 */
	ligne[30] = 9;colonne[30] = 14;coeff[30] = 1.0;	
	ligne[31] = 9;colonne[31] = 15;coeff[31] = 1.0;
	ligne[32] = 9;colonne[32] = 16;coeff[32] = 1.0;
	
	/* Contrainte Salle 10 */
	ligne[33] = 10;colonne[33] = 16;coeff[33] = 1.0;	
	ligne[34] = 10;colonne[34] = 17;coeff[34] = 1.0;
	
	
	/* chargement de la matrice dans le problème */
	
	glp_load_matrix(prob,NBCREUX,ligne,colonne,coeff); 
	
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
