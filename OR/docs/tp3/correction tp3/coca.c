/* Utilisation de GLPK en mode bibliothèque */
/* Il s'agit de l'exercice 2.8 des feuilles de TD, donné en exercice pour le TP 3 */
/* Ici, toutes les données sont saisies "en dur" dans le code, et nous nous permettons donc des allocations statiques.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

#define NBVAR 26 /* On a 13 villes donc 26 variables (les $x_i$ et les $y_i$) */
#define NBCONTR 14 /* On a 13 villes donc 14 contraintes (une par ville, et $sum_{i=1}^p y_i = P$) */ 
#define NBCREUX 117 /* Simple comptage dans l'ensemble des contraintes) */
#define P 2 /* le p du problème */

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
	
	char nomcontr[NBCONTR][7]; /* ici, les contraintes seront nommées "VilleA", "VilleB",..., "Last" */
	char numero[NBCONTR][2]; /* pour une lettre de l'alphabet */	
	char nomvar[NBVAR][3]; /* "xA", "xB", ... "yA", "yB"... */
	
	/* Création d'un problème (initialement vide) */
	
	prob = glp_create_prob(); /* allocation mémoire pour le problème */ 
	glp_set_prob_name(prob, "Coca-cola"); /* affectation d'un nom (on pourrait mettre NULL) */
	glp_set_obj_dir(prob, GLP_MAX); /* Il s'agit d'un problème de maximisation */
	
	/* Déclaration du nombre de contraintes (nombre de lignes de la matrice des contraintes) : NBCONTR */
	
	glp_add_rows(prob, NBCONTR); 

	/* On commence par préciser les bornes sur les constrainte, les indices des contraintes commencent à 1 (!) dans GLPK */

	for(i = 1;i <= NBCONTR - 1;i++)
	{
		/* partie optionnelle : donner un nom aux contraintes */
		strcpy(nomcontr[i-1], "Ville");
		sprintf(numero[i-1], "%c", 'A'+i-1);
		strcat(nomcontr[i-1], numero[i-1]); /* Les contraintes sont nommés "VilleA", "VilleB"... */		
		glp_set_row_name(prob, i, nomcontr[i-1]); /* Affectation du nom à la contrainte i */
		
		/* partie indispensable : les bornes sur les contraintes */
		glp_set_row_bnds(prob, i, GLP_UP, 0.0, 0.0); /* Les contraintes s'écrivent "... <= 0" */
	}
	
	/* partie optionnelle : donner un nom à la dernière contrainte */
	strcpy(nomcontr[NBCONTR - 1],"Last");
	glp_set_row_name(prob, NBCONTR, nomcontr[NBCONTR - 1]);
	/* partie indispensable : les bornes sur la contrainte */
	glp_set_row_bnds(prob, NBCONTR, GLP_FX, P, P); /* Cette contrainte s'écrit "... = P" */
	
	/* Déclaration du nombre de variables : NBVAR */
	
	glp_add_cols(prob, NBVAR); 
	
	/* On précise le type des variables, les indices commencent à 1 également pour les variables! */
	
	for(i = 1;i <= NBVAR/2;i++)
	{
		/* partie optionnelle : donner un nom aux variables */
		sprintf(nomvar[i-1],"x%c",'A'+i-1);
		glp_set_col_name(prob, i , nomvar[i-1]); /* Les variables sont nommées "xA", "xB"... afin de respecter les noms de variables de l'exercice 2.8 */
		
		/* partie obligatoire : bornes éventuelles sur les variables, et type */
		glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0); /* bornes sur les variables, comme sur les contraintes */
		glp_set_col_kind(prob, i, GLP_BV);	/* les variables sont par défaut continues, nous précisons ici qu'elles sont binaires avec la constante GLP_BV, on utiliserait GLP_IV pour des variables entières */	
	}
	
	for(i = NBVAR/2 + 1;i <= NBVAR;i++)
	{
		/* partie optionnelle : donner un nom aux variables */
		sprintf(nomvar[i-1],"y%c",'A'+i-1-NBVAR/2);
		glp_set_col_name(prob, i , nomvar[i-1]); /* Les variables sont nommées "yA", "yB"... afin de respecter les noms de variables de l'exercice 2.8 */
		
		/* partie obligatoire : bornes éventuelles sur les variables, et type */
		glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0); /* bornes sur les variables, comme sur les contraintes */
		glp_set_col_kind(prob, i, GLP_BV);	/* les variables sont par défaut continues, nous précisons ici qu'elles sont binaires avec la constante GLP_BV, on utiliserait GLP_IV pour des variables entières */	
	} 

	/* définition des coefficients des variables dans la fonction objectif */

	glp_set_obj_coef(prob,1,53);
	glp_set_obj_coef(prob,2,46);
	glp_set_obj_coef(prob,3,16);
	glp_set_obj_coef(prob,4,28);  
	glp_set_obj_coef(prob,5,96);  
	glp_set_obj_coef(prob,6,84);  
	glp_set_obj_coef(prob,7,32);  
	glp_set_obj_coef(prob,8,21);  
	glp_set_obj_coef(prob,9,15);  
	glp_set_obj_coef(prob,10,22);  
	glp_set_obj_coef(prob,11,41);  
	glp_set_obj_coef(prob,12,53);  
	glp_set_obj_coef(prob,13,66);
	for(i = NBVAR/2 + 1;i <= NBVAR;i++) glp_set_obj_coef(prob,i,0);
	
	/* Définition des coefficients non-nuls dans la matrice des contraintes, autrement dit les coefficients de la matrice creuse */
	/* Les indices commencent également à 1 ! */

	/* Contrainte Ville A */
	i = 1;
	ia[i] = 1;ja[i] = 1;ar[i] = 1.0;i++; // à la position (1,1) de la matrice des contraintes, on a un 1.0 (correspondant à 1.0 * x_A) 
	ia[i] = 1;ja[i] = 14;ar[i] = -1.0;i++; // à la position (1,14) de la matrice des contraintes, on a un -1.0 (correspondant à -1.0 * y_A)
	ia[i] = 1;ja[i] = 15;ar[i] = -1.0;i++; // à la position (1,15) de la matrice des contraintes, on a un -1.0 (correspondant à -1.0 * y_B)
	ia[i] = 1;ja[i] = 16;ar[i] = -1.0;i++; // à la position (1,16) de la matrice des contraintes, on a un -1.0 (correspondant à -1.0 * y_C)
	ia[i] = 1;ja[i] = 17;ar[i] = -1.0;i++; // à la position (1,17) de la matrice des contraintes, on a un -1.0 (correspondant à -1.0 * y_D)

	/* Contrainte Ville B */
	ia[i] = 2;ja[i] = 2;ar[i] = 1.0;i++; // à la position (2,2) de la matrice des contraintes, on a un 1.0 (correspondant à 1.0 * x_B) 
	ia[i] = 2;ja[i] = 14;ar[i] = -1.0;i++; // à la position (2,14) de la matrice des contraintes, on a un -1.0 (correspondant à -1.0 * y_A)
	ia[i] = 2;ja[i] = 15;ar[i] = -1.0;i++; // à la position (2,15) de la matrice des contraintes, on a un -1.0 (correspondant à -1.0 * y_B)
	ia[i] = 2;ja[i] = 16;ar[i] = -1.0;i++; // à la position (2,16) de la matrice des contraintes, on a un -1.0 (correspondant à -1.0 * y_C)
	ia[i] = 2;ja[i] = 17;ar[i] = -1.0;i++; // à la position (2,17) de la matrice des contraintes, on a un -1.0 (correspondant à -1.0 * y_D)
	ia[i] = 2;ja[i] = 18;ar[i] = -1.0;i++; // à la position (2,18) de la matrice des contraintes, on a un -1.0 (correspondant à -1.0 * y_E)
	ia[i] = 2;ja[i] = 19;ar[i] = -1.0;i++; // à la position (2,19) de la matrice des contraintes, on a un -1.0 (correspondant à -1.0 * y_F)
	ia[i] = 2;ja[i] = 20;ar[i] = -1.0;i++; // à la position (2,20) de la matrice des contraintes, on a un -1.0 (correspondant à -1.0 * y_G)

	/* Contrainte Ville C */
	ia[i] = 3;ja[i] = 3;ar[i] = 1.0;i++; // ...  
	ia[i] = 3;ja[i] = 14;ar[i] = -1.0;i++;  
	ia[i] = 3;ja[i] = 15;ar[i] = -1.0;i++;  
	ia[i] = 3;ja[i] = 16;ar[i] = -1.0;i++;  
	ia[i] = 3;ja[i] = 17;ar[i] = -1.0;i++; 
	
	/* Contrainte Ville D */
	ia[i] = 4;ja[i] = 4;ar[i] = 1.0;i++;   
	ia[i] = 4;ja[i] = 14;ar[i] = -1.0;i++;  
	ia[i] = 4;ja[i] = 15;ar[i] = -1.0;i++;  
	ia[i] = 4;ja[i] = 16;ar[i] = -1.0;i++;  
	ia[i] = 4;ja[i] = 17;ar[i] = -1.0;i++; 
	ia[i] = 4;ja[i] = 18;ar[i] = -1.0;i++; 
	ia[i] = 4;ja[i] = 19;ar[i] = -1.0;i++; 
	ia[i] = 4;ja[i] = 20;ar[i] = -1.0;i++; 
	ia[i] = 4;ja[i] = 23;ar[i] = -1.0;i++; 
	ia[i] = 4;ja[i] = 24;ar[i] = -1.0;i++; 	
	
	/* Contrainte Ville E */
	ia[i] = 5;ja[i] = 5;ar[i] = 1.0;i++;   
	ia[i] = 5;ja[i] = 15;ar[i] = -1.0;i++;  
	ia[i] = 5;ja[i] = 17;ar[i] = -1.0;i++;  
	ia[i] = 5;ja[i] = 18;ar[i] = -1.0;i++;  
	ia[i] = 5;ja[i] = 19;ar[i] = -1.0;i++; 
	ia[i] = 5;ja[i] = 20;ar[i] = -1.0;i++; 
	ia[i] = 5;ja[i] = 22;ar[i] = -1.0;i++; 
	ia[i] = 5;ja[i] = 23;ar[i] = -1.0;i++; 
	ia[i] = 5;ja[i] = 24;ar[i] = -1.0;i++; 
	
	/* Contrainte Ville F */
	ia[i] = 6;ja[i] = 6;ar[i] = 1.0;i++;   
	ia[i] = 6;ja[i] = 15;ar[i] = -1.0;i++;  
	ia[i] = 6;ja[i] = 17;ar[i] = -1.0;i++;  
	ia[i] = 6;ja[i] = 18;ar[i] = -1.0;i++;  
	ia[i] = 6;ja[i] = 19;ar[i] = -1.0;i++; 
	ia[i] = 6;ja[i] = 20;ar[i] = -1.0;i++; 
	ia[i] = 6;ja[i] = 22;ar[i] = -1.0;i++; 
	ia[i] = 6;ja[i] = 23;ar[i] = -1.0;i++; 
	ia[i] = 6;ja[i] = 24;ar[i] = -1.0;i++; 	
	
	/* Contrainte Ville G */
	ia[i] = 7;ja[i] = 7;ar[i] = 1.0;i++;   
	ia[i] = 7;ja[i] = 15;ar[i] = -1.0;i++;  
	ia[i] = 7;ja[i] = 17;ar[i] = -1.0;i++;  
	ia[i] = 7;ja[i] = 18;ar[i] = -1.0;i++;  
	ia[i] = 7;ja[i] = 19;ar[i] = -1.0;i++; 
	ia[i] = 7;ja[i] = 20;ar[i] = -1.0;i++; 
	ia[i] = 7;ja[i] = 21;ar[i] = -1.0;i++; 
	ia[i] = 7;ja[i] = 22;ar[i] = -1.0;i++; 
	ia[i] = 7;ja[i] = 23;ar[i] = -1.0;i++; 
	ia[i] = 7;ja[i] = 24;ar[i] = -1.0;i++; 	
	
	/* Contrainte Ville H */
	ia[i] = 8;ja[i] = 8;ar[i] = 1.0;i++;   
	ia[i] = 8;ja[i] = 20;ar[i] = -1.0;i++;  
	ia[i] = 8;ja[i] = 21;ar[i] = -1.0;i++;  
	ia[i] = 8;ja[i] = 22;ar[i] = -1.0;i++;  
	ia[i] = 8;ja[i] = 23;ar[i] = -1.0;i++; 
	ia[i] = 8;ja[i] = 24;ar[i] = -1.0;i++; 
	ia[i] = 8;ja[i] = 25;ar[i] = -1.0;i++; 
	ia[i] = 8;ja[i] = 26;ar[i] = -1.0;i++; 
	
	/* Contrainte Ville I */
	ia[i] = 9;ja[i] = 9;ar[i] = 1.0;i++;   
	ia[i] = 9;ja[i] = 18;ar[i] = -1.0;i++;  
	ia[i] = 9;ja[i] = 19;ar[i] = -1.0;i++;  
	ia[i] = 9;ja[i] = 20;ar[i] = -1.0;i++;  
	ia[i] = 9;ja[i] = 21;ar[i] = -1.0;i++;  
	ia[i] = 9;ja[i] = 22;ar[i] = -1.0;i++;  
	ia[i] = 9;ja[i] = 23;ar[i] = -1.0;i++; 
	ia[i] = 9;ja[i] = 24;ar[i] = -1.0;i++; 
	ia[i] = 9;ja[i] = 25;ar[i] = -1.0;i++; 
	
	/* Contrainte Ville J */
	ia[i] = 10;ja[i] = 10;ar[i] = 1.0;i++;   
	ia[i] = 10;ja[i] = 17;ar[i] = -1.0;i++;  
	ia[i] = 10;ja[i] = 18;ar[i] = -1.0;i++;  
	ia[i] = 10;ja[i] = 19;ar[i] = -1.0;i++;  
	ia[i] = 10;ja[i] = 20;ar[i] = -1.0;i++;  
	ia[i] = 10;ja[i] = 21;ar[i] = -1.0;i++;  
	ia[i] = 10;ja[i] = 22;ar[i] = -1.0;i++;  
	ia[i] = 10;ja[i] = 23;ar[i] = -1.0;i++; 
	ia[i] = 10;ja[i] = 24;ar[i] = -1.0;i++; 
	ia[i] = 10;ja[i] = 25;ar[i] = -1.0;i++;
 	
	/* Contrainte Ville K */
	ia[i] = 11;ja[i] = 11;ar[i] = 1.0;i++;   
	ia[i] = 11;ja[i] = 17;ar[i] = -1.0;i++;  
	ia[i] = 11;ja[i] = 18;ar[i] = -1.0;i++;  
	ia[i] = 11;ja[i] = 19;ar[i] = -1.0;i++;  
	ia[i] = 11;ja[i] = 20;ar[i] = -1.0;i++;  
	ia[i] = 11;ja[i] = 21;ar[i] = -1.0;i++;  
	ia[i] = 11;ja[i] = 22;ar[i] = -1.0;i++;  
	ia[i] = 11;ja[i] = 23;ar[i] = -1.0;i++; 
	ia[i] = 11;ja[i] = 24;ar[i] = -1.0;i++; 
	ia[i] = 11;ja[i] = 25;ar[i] = -1.0;i++;

	/* Contrainte Ville L */
	ia[i] = 12;ja[i] = 12;ar[i] = 1.0;i++;   
	ia[i] = 12;ja[i] = 21;ar[i] = -1.0;i++;  
	ia[i] = 12;ja[i] = 22;ar[i] = -1.0;i++;  
	ia[i] = 12;ja[i] = 23;ar[i] = -1.0;i++;  
	ia[i] = 12;ja[i] = 24;ar[i] = -1.0;i++;  
	ia[i] = 12;ja[i] = 25;ar[i] = -1.0;i++;  
	ia[i] = 12;ja[i] = 26;ar[i] = -1.0;i++;  

	/* Contrainte Ville M */
	ia[i] = 13;ja[i] = 13;ar[i] = 1.0;i++;   
	ia[i] = 13;ja[i] = 21;ar[i] = -1.0;i++;  
	ia[i] = 13;ja[i] = 25;ar[i] = -1.0;i++;  
	ia[i] = 13;ja[i] = 26;ar[i] = -1.0;i++;  
	
	/* Contrainte $\sum_{i=1}^p y_i = p$ */
	ia[i] = 14;ja[i] = 14;ar[i] = 1.0;i++;   
	ia[i] = 14;ja[i] = 15;ar[i] = 1.0;i++;  
	ia[i] = 14;ja[i] = 16;ar[i] = 1.0;i++;  
	ia[i] = 14;ja[i] = 17;ar[i] = 1.0;i++;
	ia[i] = 14;ja[i] = 18;ar[i] = 1.0;i++;   
	ia[i] = 14;ja[i] = 19;ar[i] = 1.0;i++;  
	ia[i] = 14;ja[i] = 20;ar[i] = 1.0;i++;  
	ia[i] = 14;ja[i] = 21;ar[i] = 1.0;i++;
	ia[i] = 14;ja[i] = 22;ar[i] = 1.0;i++;   
	ia[i] = 14;ja[i] = 23;ar[i] = 1.0;i++;  
	ia[i] = 14;ja[i] = 24;ar[i] = 1.0;i++;  
	ia[i] = 14;ja[i] = 25;ar[i] = 1.0;i++;
	ia[i] = 14;ja[i] = 26;ar[i] = 1.0;i++;   

	/* chargement de la matrice dans le problème */
	
	glp_load_matrix(prob,NBCREUX,ia,ja,ar); 
	
	/* Optionnel : écriture de la modélisation dans un fichier (TRES utile pour debugger!) */

	glp_write_lp(prob,NULL,"Coca-cola.lp");

	/* Résolution, puis lecture des résultats */
	
	glp_simplex(prob,NULL);	glp_intopt(prob,NULL); /* Résolution */
	z = glp_mip_obj_val(prob); /* Récupération de la valeur optimale. Dans le cas d'un problème en variables continues, l'appel est différent : z = glp_get_obj_val(prob); */
	for(i = 0;i < NBVAR; i++) x[i] = glp_mip_col_val(prob,i+1); /* Récupération de la valeur des variables, Appel différent dans le cas d'un problème en variables continues : for(i = 0;i < p.nbvar;i++) x[i] = glp_get_col_prim(prob,i+1); */

	printf("z = %lf\n",z);
	for(i = NBVAR/2;i < NBVAR;i++) printf("y%c = %d, ",'A'+i-NBVAR/2,(int)(x[i] + 0.5)); /* un cast est ajouté, x[i] pourrait être égal à 0.99999... */ 
	puts("");

	/* libération mémoire */
	glp_delete_prob(prob); 

	/* J'adore qu'un plan se déroule sans accroc! */
	return 0;
}
