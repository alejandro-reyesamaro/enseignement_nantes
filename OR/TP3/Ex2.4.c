/* Utilisation de GLPK en mode bibliothèque */
/* Il s'agit de l'exercice 2.4 des feuilles de TD */
/* Ici, les données sont séparées de la modélisation, et sont lues dans un fichier */
/* Comme nous ne connaissons pas a priori la taille du problème, des allocations dynamiques sont nécessaires */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

/* Structure contenant les données du problème */

typedef struct {
	int nbPM;     // Nombre de personnes/machines
	int nbcontr;  // Nombre de contraintes
	int nbvar;    // Nombre de variables
	int **prod;   // Productivités
	
} donnees;


/* lecture des donnees */

void lecture_data(char *file, donnees *p)
{

	FILE *fin; // Pointeur sur un fichier
	int i,j;	
	int val;
	
	fin = fopen(file,"r"); // Ouverture du fichier en lecture
	
	/* Première ligne du fichier, on lit le nombre de personnes/machines */

	fscanf(fin,"%d",&val);
	p->nbPM = val;
	
	// Nombre de contraintes
	p->nbcontr = 2 * p->nbPM;
	
	// Nombre de variables 
	p->nbvar = p->nbPM * p->nbPM;
	
	/* Cela nous permet également de dimensionner le tableau des productivités */
	/* Les indices commencent à 1 */
	p->prod = (int **) malloc((1 + p->nbPM) * sizeof(int*));
	for(i = 1;i <= p->nbPM;i++)
		p->prod[i] = (int *) malloc((1 + p->nbPM) * sizeof(int)); 
		
	/* Lecture des productivités */ 	
	for(i = 1; i <= p->nbPM; i++)
		for(j = 1; j <= p->nbPM; j++) {
			fscanf(fin,"%d",&val);
		    p->prod[i][j] = val;	
		}	
	
	fclose(fin); // Fermeture du fichier
}


int main(int argc, char *argv[])
{	
	/* Données du problème */
	
	donnees p; 

	/* structures de données propres à GLPK */
	
	glp_prob *prob; // déclaration d'un pointeur sur le problème
	int *ia;
	int *ja;
	double *ar; // déclaration des 3 tableaux servant à définir la matrice "creuse" des contraintes
	
	
    /* variables récupérant les résultats de la résolution du problème (fonction objectif et valeur des variables) */
	
	double z; 
	double *x; 
	
	/* autres déclarations */ 
	
	int i,j;
	int nbcreux; // nombre d'éléments de la matrice creuse
	int pos;     // compteur utilisé dans le remplissage de la matrice creuse
		
	/* Chargement des données à partir d'un fichier */
	
	lecture_data(argv[1],&p);
	
	/* Transfert de ces données dans les structures utilisées par la bibliothèque GLPK */
	
	prob = glp_create_prob(); /* allocation mémoire pour le problème */ 
	glp_set_prob_name(prob, "Ex2.4"); /* affectation d'un nom (on pourrait mettre NULL) */
	glp_set_obj_dir(prob, GLP_MAX); /* Il s'agit d'un problème de minimisation, on utiliserait la constante GLP_MAX dans le cas contraire */
	
	/* Déclaration du nombre de contraintes (nombre de lignes de la matrice des contraintes) : p.nbcontr */
	
	glp_add_rows(prob, p.nbcontr); 
	
	/* On commence par préciser les bornes sur les constraintes, les indices commencent à 1 (!) dans GLPK */

	for(i = 1; i <= p.nbcontr; i++)
	{
		/* partie indispensable : les bornes sur les contraintes */
		glp_set_row_bnds(prob, i, GLP_FX, 1.0, 0.0); 
		/* Avec GLPK, on peut définir simultanément deux contraintes, si par exemple, on a pour une contrainte i : "\sum x_i >= 0" et "\sum x_i <= 5",
		   on écrit alors : glp_set_row_bnds(prob, i, GLP_DB, 0.0, 5.0); la constante GLP_DB signifie qu'il y a deux bornes sur "\sum x_i" qui sont ensuite données
		   Ici, nous n'avons qu'une seule contrainte du type "\sum x_i >= p.droite[i-1]" soit une borne inférieure sur "\sum x_i", on écrit donc glp_set_row_bnds(prob, i, GLP_LO, p.droite[i-1], 0.0); le paramètre "0.0" est ignoré. 
		   Les autres constantes sont GLP_UP (borne supérieure sur le membre de gauche de la contrainte) et GLP_FX (contrainte d'égalité).   
		 Remarque : les membres de gauches des contraintes "\sum x_i ne sont pas encore saisis, les variables n'étant pas encore déclarées dans GLPK */ 
	}	

	/* Déclaration du nombre de variables : p.nbvar */
	
	glp_add_cols(prob, p.nbvar); 
	
	/* On précise le type des variables, les indices commencent à 1 également pour les variables! */
	
	for(i = 1; i <= p.nbvar; i++)
	{
		
		/* partie obligatoire : bornes éventuelles sur les variables, et type */
		glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0); /* bornes sur les variables, comme sur les contraintes */
		glp_set_col_kind(prob, i, GLP_BV);	/* les variables sont par défaut continues, nous précisons ici qu'elles sont binaires avec la constante GLP_BV, on utiliserait GLP_IV pour des variables entières */	
	} 

	/* définition des coefficients des variables dans la fonction objectif */
	for(i = 1; i <= p.nbPM; i++)
		for (j = 1; j <= p.nbPM; j++) 
	glp_set_obj_coef(prob,(i-1)*p.nbPM + j, p.prod[i][j]);  
	
	/* Définition des coefficients non-nuls dans la matrice des contraintes, autrement dit les coefficients de la matrice creuse */
	/* Les indices commencent également à 1 ! */

	nbcreux = 2 * p.nbPM * p.nbPM;
	
	ia = (int *) malloc ((1 + nbcreux) * sizeof(int));
	ja = (int *) malloc ((1 + nbcreux) * sizeof(int));
	ar = (double *) malloc ((1 + nbcreux) * sizeof(double));
	
	/* Série 1 de contraintes */
	pos = 1;
	for(i = 1; i <= p.nbPM; i++)
		for(j = 1; j <= p.nbPM; j++)
		{
			ia[pos] = i;
			ja[pos] = (i-1)*p.nbPM + j;
			ar[pos] = 1.0;
			pos++;
		}
	
	/* Série 2 de contraintes */
	for(i = 1; i <= p.nbPM; i++)
		for(j = 1; j <= p.nbPM; j++)
		{
			ia[pos] = i + p.nbPM;
			ja[pos] = i + p.nbPM * (j-1);
			ar[pos] = 1.0;
			pos++;
		}
	
	
	/* chargement de la matrice dans le problème */
	
	glp_load_matrix(prob,nbcreux,ia,ja,ar); 
	
	/* Optionnel : écriture de la modélisation dans un fichier (utile pour debugger) */

	glp_write_lp(prob,NULL,"Ex.2.4.lp");

	/* Résolution, puis lecture des résultats */
	
	glp_simplex(prob,NULL);	glp_intopt(prob,NULL); /* Résolution */
	z = glp_mip_obj_val(prob); /* Récupération de la valeur optimale. 
	
	Dans le cas d'un problème en variables continues, l'appel est différent : z = glp_get_obj_val(prob);*/
	x = (double *) malloc ((1+ p.nbvar) * sizeof(double));
	
	for(i = 1;i <= p.nbvar; i++) 
		x[i] = glp_mip_col_val(prob,i); /* Récupération de la valeur des variables, Appel différent dans le cas d'un problème en variables continues : for(i = 0;i < p.nbvar;i++) x[i] = glp_get_col_prim(prob,i+1);	*/

	printf("z = %lf\n",z);
	
	for(i = 1; i <= p.nbPM; i++) 
	{
	 	for (j = 1; j <= p.nbPM; j++)
			printf("x[%d][%d] = %d, ", i, j,(int)(x[(i-1)*p.nbPM + j] + 0.5)); /* un cast est ajouté, x[i] pourrait être égal à 0.99999... */ 
		printf("\n");
	}
	puts("");

	/* libération mémoire */
	glp_delete_prob(prob); 
	for(i = 1; i <= p.nbPM; i++) 
		free(p.prod[i]);
	free(p.prod);
	free(ia);
	free(ja);
	free(ar);
	free(x);
	
	
	/* J'adore qu'un plan se déroule sans accroc! */
	return 0;
}
