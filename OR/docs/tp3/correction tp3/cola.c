/* Utilisation de GLPK en mode bibliothèque */
/* Il s'agit de l'exercice 2.8 des feuilles de TD, donné en exercice pour le TP 3 */
/* Ici, Les données sont lues dans un fichier : modèle implicite avec quelques hypothèses restrictives (voir la fonction lecture_data) */
/* A utiliser avec le fichier "DonneesEx28.dat" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

/* Structure contenant les données du problème */

typedef struct {
	int nbvilles; // Nombre de villes
	int P; // le $p$ du problème 
	int *pop; // Tableau indiquant la population de chaque ville 
	char **voisins; // Tableau indiquant pour chaque ville, les indices (supposés des caractères, en particulier des lettres majuscules démarrant par A) des villes à moins de 25 km
	int *nbVoisins; // Tableau indiquant pour chaque ville, le nombre de villes à moins de 25 km
} donnees;

/* lecture des donnees */

void lecture_data(char *file, donnees *p)
{

	FILE *fin; // Pointeur sur un fichier
	int i,j;	
	int val;
	char valc;
	
	fin = fopen(file,"r"); // Ouverture du fichier en lecture
	
	/* Première ligne du fichier, on lit le nombre de villes puis le $P$ du problème */

	fscanf(fin,"%d",&val);
	p->nbvilles = val;
	fscanf(fin,"%d",&val);
	p->P = val;
		
	/* On peut maintenant faire les allocations dynamiques dépendant du nombre de villes */
	
	p->pop = (int *) malloc (p->nbvilles * sizeof(int));  
	p->nbVoisins = (int *) malloc (p->nbvilles * sizeof(int));
	p->voisins = (char **) malloc (p->nbvilles * sizeof(char *)); /* La taille des "lignes" reste à dimensionner */
	
	/* Deuxième ligne du fichier, on lit les coefficients de la fonction objectif */
	
	for(i = 0;i < p->nbvilles;i++)
	{
		fscanf(fin,"%d",&val);
		p->pop[i] = val;
	}
		
	/* On lit ensuite les voisins de chaque ville */
	
	for(i = 0;i < p->nbvilles;i++) // Pour chaque ville,
	{
		// Lecture du nombre de villes à moins de 25 km de la ville considérée, permettant ensuite de dimensionner correctement la "ligne" correspondante
		fscanf(fin,"%d",&val);
		p->nbVoisins[i] = val;
		p->voisins[i] = (char *) malloc (p->nbVoisins[i] * sizeof(char));
		
		// Lecture des indices des villes voisines
		for(j = 0;j < p->nbVoisins[i];j++)
		{
			fscanf(fin," %c",&valc);
			p->voisins[i][j] = valc;
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
	glp_set_prob_name(prob, "Coca-cola"); /* affectation d'un nom (on pourrait mettre NULL) */
	glp_set_obj_dir(prob, GLP_MAX); /* Il s'agit d'un problème de maximisation */
	
	/* Déclaration du nombre de contraintes (nombre de lignes de la matrice des contraintes) : (p.nbvilles) + 1 */
	
	glp_add_rows(prob, (p.nbvilles) + 1); 
	nomcontr = (char **) malloc (((p.nbvilles) + 1) * sizeof(char *));
	numero = (char **) malloc (((p.nbvilles) + 1) * sizeof(char *)); 

	/* On commence par préciser les bornes sur les constrainte, les indices commencent à 1 (!) dans GLPK */

	for(i=1;i<=p.nbvilles;i++)
	{
		/* partie optionnelle : donner un nom aux contraintes */
		
		nomcontr[i-1] = (char *) malloc (7 * sizeof(char)); // Hypothèse simplificatrice : on suppose que les noms de contraintes font 6 caractères maximum */
		numero[i-1] = (char *) malloc (2 * sizeof(char)); // Ici, il s'agit simplement d'une lettre
		strcpy(nomcontr[i-1], "Ville");
		sprintf(numero[i-1], "%c", 'A'+i-1);
		strcat(nomcontr[i-1], numero[i-1]); /* Les contraintes sont nommés "VilleA", "VilleB"... */		
		glp_set_row_name(prob, i, nomcontr[i-1]); /* Affectation du nom à la contrainte i */
		
		/* partie indispensable : les bornes sur les contraintes */
		glp_set_row_bnds(prob, i, GLP_UP, 0.0, 0.0); /* Les contraintes s'écrivent "... <= 0" */
	}	

	/* partie optionnelle : donner un nom à la dernière contrainte */
	nomcontr[p.nbvilles] = (char *) malloc (5 * sizeof(char));
	strcpy(nomcontr[p.nbvilles],"Last");
	glp_set_row_name(prob, (p.nbvilles) + 1, nomcontr[p.nbvilles]);
	/* partie indispensable : les bornes sur la contrainte */
	glp_set_row_bnds(prob, (p.nbvilles) + 1, GLP_FX, p.P, p.P); /* Cette contrainte s'écrit "... = P" */

	/* Déclaration du nombre de variables : 2 * p.nbvilles */
	
	glp_add_cols(prob, 2 * (p.nbvilles)); 
	nomvar = (char **) malloc (2 * (p.nbvilles) * sizeof(char *));
	
	/* On précise le type des variables, les indices commencent à 1 également pour les variables! */
	
	for(i = 1;i <= p.nbvilles;i++)
	{
		/* partie optionnelle : donner un nom aux variables */
		nomvar[i-1] = (char *) malloc (3 * sizeof(char));
		sprintf(nomvar[i-1],"x%c",'A'+i-1);
		glp_set_col_name(prob, i , nomvar[i-1]); /* Les variables sont nommées "xA", "xB"... afin de respecter les noms de variables de l'exercice 2.8 */
		
		/* partie obligatoire : bornes éventuelles sur les variables, et type */
		glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0); /* bornes sur les variables, comme sur les contraintes */
		glp_set_col_kind(prob, i, GLP_BV);	/* les variables sont par défaut continues, nous précisons ici qu'elles sont binaires avec la constante GLP_BV, on utiliserait GLP_IV pour des variables entières */	
	}
	
	for(i = p.nbvilles + 1;i <= 2 * p.nbvilles;i++)
	{
		/* partie optionnelle : donner un nom aux variables */
		nomvar[i-1] = (char *) malloc (3 * sizeof(char));
		sprintf(nomvar[i-1],"y%c",'A'+i-1-p.nbvilles);
		glp_set_col_name(prob, i , nomvar[i-1]); /* Les variables sont nommées "yA", "yB"... afin de respecter les noms de variables de l'exercice 2.8 */
		
		/* partie obligatoire : bornes éventuelles sur les variables, et type */
		glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0); /* bornes sur les variables, comme sur les contraintes */
		glp_set_col_kind(prob, i, GLP_BV);	/* les variables sont par défaut continues, nous précisons ici qu'elles sont binaires avec la constante GLP_BV, on utiliserait GLP_IV pour des variables entières */	
	} 

	/* définition des coefficients des variables dans la fonction objectif */

	for(i = 1;i <= p.nbvilles;i++) glp_set_obj_coef(prob,i,p.pop[i - 1]);
	for(i = p.nbvilles + 1;i <= 2 * p.nbvilles;i++) glp_set_obj_coef(prob,i,0.0);
	
	/* Définition des coefficients non-nuls dans la matrice des contraintes, autrement dit les coefficients de la matrice creuse */
	/* Les indices commencent également à 1 ! */

	nbcreux = p.nbvilles; 
	for(i = 0;i < p.nbvilles;i++) nbcreux += p.nbVoisins[i] + 1; // Comptage du nombre d'éléments non-creux
	
	ia = (int *) malloc ((1 + nbcreux) * sizeof(int));
	ja = (int *) malloc ((1 + nbcreux) * sizeof(int));
	ar = (double *) malloc ((1 + nbcreux) * sizeof(double));
	
	pos = 1;
	for(i = 0;i < p.nbvilles;i++) // Pour chaque ville, on a une contrainte...
	{
		ia[pos] = i + 1;
		ja[pos] = i + 1;
		ar[pos] = 1.0; // $+ x_{i + 1}$
		pos++;
		for(j = 0;j < p.nbVoisins[i];j++)
		{
			ia[pos] = i + 1;
			ja[pos] = p.voisins[i][j] - 'A' + 14; // calcul du bon indice $j$ pour $y_j$
			ar[pos] = -1.0; 
			pos++;
		}
	}
	
	for(i = 0;i < p.nbvilles;i++) // dernière contrainte
	{
		ia[pos] = p.nbvilles + 1;
		ja[pos] = p.nbvilles + 1 + i;
		ar[pos] = 1.0; // $+ y_{i + 1}$
		pos++;
	}
	
	/* chargement de la matrice dans le problème */
	
	glp_load_matrix(prob,nbcreux,ia,ja,ar); 
	
	/* Optionnel : écriture de la modélisation dans un fichier (TRES utile pour debugger!) */
	
	glp_write_lp(prob,NULL,"Coca-cola.lp");
	
	/* Résolution, puis lecture des résultats */
	
	glp_simplex(prob,NULL);	glp_intopt(prob,NULL); /* Résolution */
	z = glp_mip_obj_val(prob); /* Récupération de la valeur optimale. Dans le cas d'un problème en variables continues, l'appel est différent : z = glp_get_obj_val(prob); */
	x = (double *) malloc (2 * p.nbvilles * sizeof(double));
	for(i = 0;i < 2 * p.nbvilles; i++) x[i] = glp_mip_col_val(prob,i+1); /* Récupération de la valeur des variables, Appel différent dans le cas d'un problème en variables continues : for(i = 0;i < p.nbvar;i++) x[i] = glp_get_col_prim(prob,i+1); */

	printf("z = %lf\n",z);
	for(i = p.nbvilles;i < 2 * p.nbvilles;i++) printf("y%c = %d, ",'A'+i-p.nbvilles,(int)(x[i] + 0.5)); 
	puts("");
	
	/* libération mémoire */
	glp_delete_prob(prob); 
	
	free(p.pop);
	free(p.nbVoisins);
	for(i = 0;i < p.nbvilles;i++) free(p.voisins[i]);
	free(p.voisins);
	free(x);
	for(i = 0;i < (p.nbvilles) + 1;i++)
	{
		free(nomcontr[i]);
		free(numero[i]);
	}
	free(nomcontr);
	free(numero);
	for(i = 0;i < 2 * p.nbvilles;i++) free(nomvar[i]);
	free(nomvar);

	/* J'adore qu'un plan se déroule sans accroc! */
	return 0;
}
