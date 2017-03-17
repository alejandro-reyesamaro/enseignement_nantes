#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

/* Structure contenant les données du problème */

typedef struct {
	int nb_points_choix; // Nombre de variables
	int *gains; // Tableau des gains
} donnees_prob_affect; // structure de données définissant un problème d'affectation


/* lecture des donnees */

void lecture_data(char *file, donnees_prob_affect *p)
{

	FILE *fin; // Pointeur sur un fichier
	int i,j;	
	int val;
	
	fin = fopen(file,"r"); // Ouverture du fichier en lecture
	
	/* Première ligne du fichier, on lit le nombre de colonnes (obligatoirement égal au nombre de lignes),
	c'est à dire le nombre d'élément que l'on devra affecter à un nombre égal d'emplacements*/

	fscanf(fin,"%d",&val);
	p->nb_points_choix = val;
		
	/* On peut maintenant faire l'allocations dynamiques du tableau des coefficients de la fonction objectif*/
	
	p->gains = (int *) malloc (p->nb_points_choix * p->nb_points_choix * sizeof(int));
	
	/* Deuxième ligne du fichier, on lit et on affecte les coefficients de la fonction objectif */
	
	for(i = 0; i < p->nb_points_choix * p->nb_points_choix ; i++)
	{
		fscanf(fin,"%d",&val);
		p->gains[i] = val;
	}
	fclose(fin); // Fermeture du fichier
}


int main(int argc, char *argv[])
{	
	/* Données du problème */
	
	donnees_prob_affect p; 

	/* structures de données propres à GLPK */
	
	glp_prob *prob; // déclaration d'un pointeur sur le problème
	int *ia;
	int *ja;
	double *ar; // déclaration des 3 tableaux servant à définir la matrice "creuse" des contraintes
	
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
	
	lecture_data(argv[1],&p);

	/* Transfert de ces données dans les structures utilisées par la bibliothèque GLPK */
	
	prob = glp_create_prob(); /* allocation mémoire pour le problème */ 
	glp_set_prob_name(prob, "affectation_Ex2-4"); /* affectation d'un nom (on pourrait mettre NULL) */
	glp_set_obj_dir(prob, GLP_MAX);
	
	/* Déclaration du nombre de contraintes (nombre de lignes de la matrice des contraintes) : p.nbcontr */
	
	glp_add_rows(prob, p.nb_points_choix * 2); 
	nomcontr = (char **) malloc (p.nb_points_choix * 2 * sizeof(char *));
	numero = (char **) malloc (p.nb_points_choix * 2 * sizeof(char *)); 

	/* On commence par préciser les bornes sur les constrainte, les indices commencent à 1 (!) dans GLPK */

	for(i=1;i<=p.nb_points_choix;i++)
	{
		/* partie optionnelle : donner un nom aux contraintes */
		nomcontr[i - 1] = (char *) malloc (8 * sizeof(char)); // hypothèse simplificatrice : on a au plus 7 caractères, sinon il faudrait dimensionner plus large! 
		numero[i - 1] = (char *) malloc (3  * sizeof(char)); // Même hypothèse sur la taille du problème
		strcpy(nomcontr[i-1], "pers_");
		sprintf(numero[i-1], "%d", i);
		strcat(nomcontr[i-1], numero[i-1]); /* Les contraintes sont nommés "salle1", "salle2"... */		
		glp_set_row_name(prob, i, nomcontr[i-1]); /* Affectation au nom à la contrainte i */
		
		/* partie indispensable : les bornes sur les contraintes */
		glp_set_row_bnds(prob, i, GLP_FX, 1.0, 1.0); 
	}

	for(i=p. nb_points_choix ; i<=p.nb_points_choix * 2 - 1 ;i++)
	{
		/* partie optionnelle : donner un nom aux contraintes */
		nomcontr[i - 1] = (char *) malloc (8 * sizeof(char)); // hypothèse simplificatrice : on a au plus 7 caractères, sinon il faudrait dimensionner plus large! 
		numero[i - 1] = (char *) malloc (3  * sizeof(char)); // Même hypothèse sur la taille du problème
		strcpy(nomcontr[i-1], "mach_");
		sprintf(numero[i-1], "%d", i);
		strcat(nomcontr[i-1], numero[i-1]); /* Les contraintes sont nommés "salle1", "salle2"... */		
		glp_set_row_name(prob, i, nomcontr[i-1]); /* Affectation du nom à la contrainte i */
		
		/* partie indispensable : les bornes sur les contraintes */
		glp_set_row_bnds(prob, i, GLP_FX, 1.0, 1.0); 
		/* Avec GLPK, on peut définir simultanément deux contraintes, si par exemple, on a pour une contrainte i : "\sum x_i >= 0" et "\sum x_i <= 5",
		   on écrit alors : glp_set_row_bnds(prob, i, GLP_DB, 0.0, 5.0); la constante GLP_DB signifie qu'il y a deux bornes sur "\sum x_i" qui sont ensuite données
		   Ici, nous n'avons qu'une seule contrainte du type "\sum x_i >= p.droite[i-1]" soit une borne inférieure sur "\sum x_i", on écrit donc glp_set_row_bnds(prob, i, GLP_LO, p.droite[i-1], 0.0); le paramètre "0.0" est ignoré. 
		   Les autres constantes sont GLP_UP (borne supérieure sur le membre de gauche de la contrainte) et GLP_FX (contrainte d'égalité).   
		 Remarque : les membres de gauches des contraintes "\sum x_i ne sont pas encore saisis, les variables n'étant pas encore déclarées dans GLPK */ 
	}

	/* Déclaration du nombre de variables : p.nbvar */
	
	glp_add_cols(prob, p.nb_points_choix * p.nb_points_choix); 
	nomvar = (char **) malloc (p.nb_points_choix * p.nb_points_choix * sizeof(char *));
	
	/* On précise le type des variables, les indices commencent à 1 également pour les variables! */
	
	for(i=1; i<=p.nb_points_choix * p.nb_points_choix ;i++)
	{
		/* partie optionnelle : donner un nom aux variables */
		nomvar[i - 1] = (char *) malloc (3 * sizeof(char));
		sprintf(nomvar[i-1],"x%d%d",i % 6, ((i - 1)/ 6) + 1);
		glp_set_col_name(prob, i , nomvar[i-1]); /* Les variables sont nommées "xA", "xB"... afin de respecter les noms de variables de l'exercice 2.2 */

		/* partie obligatoire : bornes éventuelles sur les variables, et type */
		glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0); /* bornes sur les variables, comme sur les contraintes */
		glp_set_col_kind(prob, i, GLP_BV);	/* les variables sont par défaut continues, nous précisons ici qu'elles sont binaires avec la constante GLP_BV, on utiliserait GLP_IV pour des variables entières */	
	} 
	/* définition des coefficients des variables dans la fonction objectif */

	for(i = 1;i <= p.nb_points_choix * p.nb_points_choix ;i++){ glp_set_obj_coef(prob,i,p.gains[i - 1]);}
	/* Définition des coefficients non-nuls dans la matrice des contraintes, autrement dit les coefficients de la matrice creuse */
	/* Les indices commencent également à 1 ! */

	nbcreux = p.nb_points_choix * p.nb_points_choix * 2;
	
	ia = (int *) malloc ((1 + nbcreux) * sizeof(int));
	ja = (int *) malloc ((1 + nbcreux) * sizeof(int));
	ar = (double *) malloc ((1 + nbcreux) * sizeof(double));
	
	pos = 1;
	for(i = 0;i < p.nb_points_choix * 2;i++)
	{
		if (i < p.nb_points_choix)
		{
			for(j = 0;j < p.nb_points_choix;j++)
			{
				ia[pos] = i + 1;
				ja[pos] = p.nb_points_choix * i + j + 1 ;
				ar[pos] = 1.0;
				pos++;
			}
		}
		else
		{
			for(j = 0; j < p.nb_points_choix;j++)
			{
				ia[pos] = i + 1;
				ja[pos] = i + j * p.nb_points_choix + 1 - 6;
				ar[pos] = 1.0;
				pos++;
	
			}
		}
	}
	
	/* chargement de la matrice dans le problème */
	
	glp_load_matrix(prob,nbcreux,ia,ja,ar); 
	
	/* Optionnel : écriture de la modélisation dans un fichier (utile pour debugger) */

	glp_write_lp(prob,NULL,"ex2-4.lp");

	/* Résolution, puis lecture des résultats */
	
	glp_simplex(prob,NULL);	glp_intopt(prob,NULL); /* Résolution */
	z = glp_mip_obj_val(prob); /* Récupération de la valeur optimale. Dans le cas d'un problème en variables continues, l'appel est différent : z = glp_get_obj_val(prob);*/
	x = (double *) malloc (p.nb_points_choix * p.nb_points_choix * sizeof(double));
	for(i = 0;i < p.nb_points_choix * p.nb_points_choix; i++) x[i] = glp_mip_col_val(prob,i+1); /* Récupération de la valeur des variables, Appel différent dans le cas d'un problème en variables continues : for(i = 0;i < p.nbvar;i++) x[i] = glp_get_col_prim(prob,i+1);	*/

	printf("z = %lf\n",z);
	for(i = 0;i < p.nb_points_choix;i++) 
	{	
		for(j = 0; j < p.nb_points_choix;j++)
		{
			printf("x%d = %d, 	",i * p.nb_points_choix + j,(int)(x[i * p.nb_points_choix + j] + 0.5));
		}
		printf("\n");
	} /* un cast est ajouté, x[i] pourrait être égal à 0.99999... */ 
	puts("");

	/* libération mémoire */
	glp_delete_prob(prob);
	return 0;
}
