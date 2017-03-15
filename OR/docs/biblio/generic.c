/* Utilisation de GLPK en mode bibliothèque */
/* Il s'agit de l'exercice 2.2 des feuilles de TD, qui a servi à illustrer l'utilisation d'une matrice creuse avec GNUMathProg */
/* Ici, les données sont séparées de la modélisation, et sont lues dans un fichier */
/* Comme nous ne connaissons pas a priori la taille du problème, des allocations dynamiques sont nécessaires */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

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
	glp_set_prob_name(prob, "musee"); /* affectation d'un nom (on pourrait mettre NULL) */
	glp_set_obj_dir(prob, GLP_MIN); /* Il s'agit d'un problème de minimisation, on utiliserait la constante GLP_MAX dans le cas contraire */
	
	/* Déclaration du nombre de contraintes (nombre de lignes de la matrice des contraintes) : p.nbcontr */
	
	glp_add_rows(prob, p.nbcontr); 
	nomcontr = (char **) malloc (p.nbcontr * sizeof(char *));
	numero = (char **) malloc (p.nbcontr * sizeof(char *)); 

	/* On commence par préciser les bornes sur les constrainte, les indices commencent à 1 (!) dans GLPK */

	for(i=1;i<=p.nbcontr;i++)
	{
		/* partie optionnelle : donner un nom aux contraintes */
		nomcontr[i - 1] = (char *) malloc (8 * sizeof(char)); // hypothèse simplificatrice : on a au plus 7 caractères, sinon il faudrait dimensionner plus large! 
		numero[i - 1] = (char *) malloc (3  * sizeof(char)); // Même hypothèse sur la taille du problème
		strcpy(nomcontr[i-1], "salle");
		sprintf(numero[i-1], "%d", i);
		strcat(nomcontr[i-1], numero[i-1]); /* Les contraintes sont nommés "salle1", "salle2"... */		
		glp_set_row_name(prob, i, nomcontr[i-1]); /* Affectation du nom à la contrainte i */
		
		/* partie indispensable : les bornes sur les contraintes */
		glp_set_row_bnds(prob, i, GLP_LO, p.droite[i-1], 0.0); 
		/* Avec GLPK, on peut définir simultanément deux contraintes, si par exemple, on a pour une contrainte i : "\sum x_i >= 0" et "\sum x_i <= 5",
		   on écrit alors : glp_set_row_bnds(prob, i, GLP_DB, 0.0, 5.0); la constante GLP_DB signifie qu'il y a deux bornes sur "\sum x_i" qui sont ensuite données
		   Ici, nous n'avons qu'une seule contrainte du type "\sum x_i >= p.droite[i-1]" soit une borne inférieure sur "\sum x_i", on écrit donc glp_set_row_bnds(prob, i, GLP_LO, p.droite[i-1], 0.0); le paramètre "0.0" est ignoré. 
		   Les autres constantes sont GLP_UP (borne supérieure sur le membre de gauche de la contrainte) et GLP_FX (contrainte d'égalité).   
		 Remarque : les membres de gauches des contraintes "\sum x_i ne sont pas encore saisis, les variables n'étant pas encore déclarées dans GLPK */ 
	}	

	/* Déclaration du nombre de variables : p.nbvar */
	
	glp_add_cols(prob, p.nbvar); 
	nomvar = (char **) malloc (p.nbvar * sizeof(char *));
	
	/* On précise le type des variables, les indices commencent à 1 également pour les variables! */
	
	for(i=1;i<=p.nbvar;i++)
	{
		/* partie optionnelle : donner un nom aux variables */
		nomvar[i - 1] = (char *) malloc (3 * sizeof(char));
		sprintf(nomvar[i-1],"x%c",'B'+i-1);
		glp_set_col_name(prob, i , nomvar[i-1]); /* Les variables sont nommées "xA", "xB"... afin de respecter les noms de variables de l'exercice 2.2 */

		/* partie obligatoire : bornes éventuelles sur les variables, et type */
		glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0); /* bornes sur les variables, comme sur les contraintes */
		glp_set_col_kind(prob, i, GLP_BV);	/* les variables sont par défaut continues, nous précisons ici qu'elles sont binaires avec la constante GLP_BV, on utiliserait GLP_IV pour des variables entières */	
	} 

	/* définition des coefficients des variables dans la fonction objectif */

	for(i = 1;i <= p.nbvar;i++) glp_set_obj_coef(prob,i,p.couts[i - i]);  
	
	/* Définition des coefficients non-nuls dans la matrice des contraintes, autrement dit les coefficients de la matrice creuse */
	/* Les indices commencent également à 1 ! */

	nbcreux = 0;
	for(i = 0;i < p.nbcontr;i++) nbcreux += p.sizeContr[i];
	
	ia = (int *) malloc ((1 + nbcreux) * sizeof(int));
	ja = (int *) malloc ((1 + nbcreux) * sizeof(int));
	ar = (double *) malloc ((1 + nbcreux) * sizeof(double));
	
	pos = 1;
	for(i = 0;i < p.nbcontr;i++)
	{
		for(j = 0;j < p.sizeContr[i];j++)
		{
			ia[pos] = i + 1;
			ja[pos] = p.contr[i][j];
			ar[pos] = 1.0;
			pos++;
		}
	}
	
	/* chargement de la matrice dans le problème */
	
	glp_load_matrix(prob,nbcreux,ia,ja,ar); 
	
	/* Optionnel : écriture de la modélisation dans un fichier (utile pour debugger) */

	glp_write_lp(prob,NULL,"musee.lp");

	/* Résolution, puis lecture des résultats */
	
	glp_simplex(prob,NULL);	glp_intopt(prob,NULL); /* Résolution */
	z = glp_mip_obj_val(prob); /* Récupération de la valeur optimale. Dans le cas d'un problème en variables continues, l'appel est différent : z = glp_get_obj_val(prob);*/
	x = (double *) malloc (p.nbvar * sizeof(double));
	for(i = 0;i < p.nbvar; i++) x[i] = glp_mip_col_val(prob,i+1); /* Récupération de la valeur des variables, Appel différent dans le cas d'un problème en variables continues : for(i = 0;i < p.nbvar;i++) x[i] = glp_get_col_prim(prob,i+1);	*/

	printf("z = %lf\n",z);
	for(i = 0;i < p.nbvar;i++) printf("x%c = %d, ",'B'+i,(int)(x[i] + 0.5)); /* un cast est ajouté, x[i] pourrait être égal à 0.99999... */ 
	puts("");

	/* libération mémoire */
	glp_delete_prob(prob); 
	free(p.couts);
	free(p.sizeContr);
	free(p.droite);
	for(i = 0;i < p.nbcontr;i++) free(p.contr[i]);
	free(p.contr);
	free(ia);
	free(ja);
	free(ar);
	free(x);

	/* J'adore qu'un plan se déroule sans accroc! */
	return 0;
}
