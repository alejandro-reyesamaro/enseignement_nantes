/* TSCHAN Romain */
/* M'SOILI Roihil */
/* 601A */

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
	int nbvar; // Nombre de variables
	int nbcontr; // Nombre de contraintes 
	int *coefs; // Tableau des coefs
	int sizeContr; // Tableau des nombres de variables dans chacune des contraintes
	int *droite; // Tableau des valeurs des membres de droites des contraintes
} donnees;


/* lecture des données */

void lecture_data(char *file, donnees *p)
{

	FILE *fin; // Pointeur sur un fichier
	int i,j;	
	int val;
	
	fin = fopen(file,"r"); // Ouverture du fichier en lecture
	
	/* Première ligne du fichier, on lit la taille val du tableau (qui est carré, celui de l'énoncé fait 6*6) du problème. */
	/* Étant donné le problème, le nombre de variables est val*val et le nombre de contraintes est val*2. */

	fscanf(fin,"%d",&val);
	p->nbvar = val*val;
	p->nbcontr = val*2;
	p->sizeContr = val; //6 coefficients par contrainte
	
	/* On peut maintenant faire les allocations dynamiques dépendant du nombre de variables et du nombre de contraintes */
	
	p->coefs = (int *) malloc (p->nbvar * sizeof(int)); //36 coefficients
	p->droite = (int *) malloc (p->nbcontr * sizeof(int)); //12 membres de droite	
	
	
	/* Suite du fichier, on lit les coefficients de la fonction objectif */
	for(i = 0;i < p->nbvar;i++) {
		fscanf(fin,"%d",&val);
		p->coefs[i] = val;
	}	
	
	fclose(fin); // Fermeture du fichier
	
	// membres de droite des contraintes
	for(i = 0;i < p->nbcontr;i++) {
		p->droite[i] = 1;
	}
}

int main(int argc, char *argv[])
{	
	/* Données du problème */
	
	donnees p; 

	/* structures de données propres à GLPK */
	
	glp_prob *prob; // déclaration d'un pointeur sur le problème
	int *t_lignes;
	int *t_colonnes;
	double *t_valeurs; // déclaration des 3 tableaux servant à définir la matrice "creuse" des contraintes
	
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
	glp_set_prob_name(prob, "affectations ex 2.4"); /* affectation d'un nom (on pourrait mettre NULL) ; on lui affecte le nom "affectations" parce
												que c'est un problème d'affectation, n'est-ce pas cocasse ? */
	glp_set_obj_dir(prob, GLP_MAX); /* Il s'agit d'un problème de maximisation */
	
	/* Déclaration du nombre de contraintes (nombre de lignes de la matrice des contraintes) : p.nbcontr */
	
	glp_add_rows(prob, p.nbcontr); 
	nomcontr = (char **) malloc (p.nbcontr * sizeof(char *));
	numero = (char **) malloc (p.nbcontr * sizeof(char *)); 

	/* On commence par préciser les bornes sur les contraintes, les indices commencent à 1 (!) dans GLPK */

	// contraintes sur les personnes
	for(i=1;i<=p.nbcontr/2;i++)	{
		/* partie optionnelle : donner un nom aux contraintes */
		nomcontr[i - 1] = (char *) malloc (8 * sizeof(char)); // hypothèse simplificatrice : on a au plus 7 caractères, sinon il faudrait dimensionner plus large! 
		numero[i - 1] = (char *) malloc (3  * sizeof(char)); // Même hypothèse sur la taille du problème
		strcpy(nomcontr[i-1], "personne");
		sprintf(numero[i-1], "%d", i);
		strcat(nomcontr[i-1], numero[i-1]); /* Les contraintes sont nommés "salle1", "salle2"... */		
		glp_set_row_name(prob, i, nomcontr[i-1]); /* Affectation du nom à la contrainte i */
		
		/* partie indispensable : les bornes sur les contraintes */
		glp_set_row_bnds(prob, i, GLP_FX, p.droite[i-1], p.droite[i-1]);
		
		/* Ici, nous n'avons une contrainte du type GLP_FX (contrainte d'égalité). */ 
	}
	
	// contraintes sur les machines
	for(i=(p.nbcontr/2)+1;i<=p.nbcontr;i++)	{
		/* partie optionnelle : donner un nom aux contraintes */
		nomcontr[i - 1] = (char *) malloc (8 * sizeof(char)); // hypothèse simplificatrice : on a au plus 7 caractères, sinon il faudrait dimensionner plus large! 
		numero[i - 1] = (char *) malloc (3  * sizeof(char)); // Même hypothèse sur la taille du problème
		strcpy(nomcontr[i-1], "machine");
		sprintf(numero[i-1], "%d", i-p.nbcontr/2);
		strcat(nomcontr[i-1], numero[i-1]); /* Les contraintes sont nommés "salle1", "salle2"... */		
		glp_set_row_name(prob, i, nomcontr[i-1]); /* Affectation du nom à la contrainte i */
		
		/* partie indispensable : les bornes sur les contraintes */
		glp_set_row_bnds(prob, i, GLP_FX, p.droite[i-1], p.droite[i-1]);
		
		/* Ici, nous n'avons une contraintes du type GLP_FX (contrainte d'égalité). */ 
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

	for(i = 1;i <= p.nbvar;i++) {
		glp_set_obj_coef(prob,i,p.coefs[i - 1]);
	}
	
	/* Définition des coefficients non-nuls dans la matrice des contraintes, autrement dit les coefficients de la matrice creuse */
	/* Les indices commencent également à 1 ! */

	nbcreux = 72; //12 contraintes * 6 variables par contraintes = 72
	
	t_lignes = (int *) malloc ((1 + nbcreux) * sizeof(int));		// numéro de la contrainte
	t_colonnes = (int *) malloc ((1 + nbcreux) * sizeof(int));		// numéro de la variable.
		//C'est un tableau à une dimension mais ça correspond à un tableau à 2 dimensions en fait.
		
	t_valeurs = (double *) malloc ((1 + nbcreux) * sizeof(double));	// vaut 1 si le coefficient intervient dans la contrainte.
	
	pos = 1;
	for(i = 0;i < p.nbcontr/2;i++) // contraintes sur les lignes (personnes)
	{
		for(j = 0;j < p.sizeContr;j++)
		{
			t_lignes[pos] = i + 1;
			t_colonnes[pos] = (i*p.sizeContr) + j+1;
			t_valeurs[pos] = 1.0;
			pos++;
		}
	}
	
	for(i = p.nbcontr/2;i < p.nbcontr;i++) // contraintes sur les colonnes (machines)
	{
		for(j = 0;j < p.sizeContr;j++)
		{
			t_lignes[pos] = i+1;
			t_colonnes[pos] = (i-p.nbcontr/2)+1+(j*p.sizeContr);
			t_valeurs[pos] = 1.0;
			pos++;
		}
	}
	
	/*
	int k;
	for(k=1;k<pos;k++) {
		printf("k = %d - ", k);
		printf("ligne %d - ", t_lignes[k]);
		printf("colonne %d - ", t_colonnes[k]);
		printf("valeur %f \n", t_valeurs[k]);
	}
	*/
	
	/* chargement de la matrice dans le problème */
	
	glp_load_matrix(prob,nbcreux,t_lignes,t_colonnes,t_valeurs); 
	
	/* Optionnel : écriture de la modélisation dans un fichier (utile pour debugger) */

	glp_write_lp(prob,NULL,"ex2-4.lp");

	/* Résolution, puis lecture des résultats */
	
	glp_simplex(prob,NULL);	glp_intopt(prob,NULL); /* Résolution */
	z = glp_mip_obj_val(prob); /* Récupération de la valeur optimale. Dans le cas d'un problème en variables continues, l'appel est différent : z = glp_get_obj_val(prob);*/
	x = (double *) malloc (p.nbvar * sizeof(double));
	
	for(i = 0;i < p.nbvar; i++) x[i] = glp_mip_col_val(prob,i+1); /* Récupération de la valeur des variables, Appel différent dans le cas d'un problème en variables continues : for(i = 0;i < p.nbvar;i++) x[i] = glp_get_col_prim(prob,i+1);	*/

	printf("z = %lf\n",z);
	for(i = 0;i < p.nbvar;i++) printf("x%c = %d, \t",'B'+i,(int)(x[i] + 0.5)); /* un cast est ajouté, x[i] pourrait être égal à 0.99999... */ 
	puts("");

	/* libération mémoire */
	glp_delete_prob(prob); 
	free(p.coefs);
	free(p.droite);

	/* 
	
	(•_•)
	
	Et voilà un problème qu'on a résolu...
	
	( •_•)>⌐■-■
	
	...sans problème.
	
	(⌐■_■)
	
	*/
	return 0;
}

