/* 
   Exercice 2.4 du td modélisé en C (modèle implicite)
   Chedotal Corentin & Duclos Romain - 601A
   06-03-2017
*/

// Bibliothèques usuelles plus GLPK
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glpk.h>

// Structure de données pour stocker toutes les données du problème
typedef struct {
	int nbvar; //n
	int nbcontr; //m
	int *couts; //Tableau des coefficients de chaque variable dans la fonction objectif
	int **contr; //Tableau de tableaux indiquant les indices des variables dans chaque contrainte
	int *sizeContr; //Tableau contenant le nombre de variables dans chaque contrainte
	int *droite; //Tableau des coefficients de droite dans les contraintes
} donnees;

//Méthode pour lire les données
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
	//Données du problème
	donnees p;

	//Pointeur sur le problème
	glp_prob *prob;

	//Indices de boucles
	int i;
	int j;

	//Déclaration et allocation mémoire des trois tableaux
	int *ia;
	int *ja;
	double *ar;

	//Nombre de creux de la matrice des contraintes
	int nbcreux;

	//Indice pour le remplissage des tableaux de la matrice creuse
	int pos;

	//Variables pour la récupération des résultats
	double z;
	double *x;

	//Récupération des données
	lecture_data(argv[1],&p);

	//Allocation mémoire au problème
	prob = glp_create_prob();

	//Affectation d'un nom
	glp_set_prob_name(prob, "affectMachines");

	//Sens d'optimisation
	glp_set_obj_dir(prob, GLP_MAX);

	//On a p.nbcontr contraintes
	glp_add_rows(prob, p.nbcontr);

	//Bornes sur les contraintes
	for (i = 1; i <= p.nbcontr; i++)
	{
		glp_set_row_bnds(prob, i, GLP_FX, p.droite[i-1], 0.0);
	}

	//On a p.nbvar variables
	//Donc p.nbvar colonnes
	glp_add_cols(prob, p.nbvar);

	//Pour chaque variable
	for(i = 1; i <= p.nbvar; ++i)
	{
		//Bornes sur les variables 0 <= xi <= 1
		glp_set_col_bnds(prob,i,GLP_DB,0.0,1.0);
	
		//Type des variables (ici binaire -> GLP_BV)
		glp_set_col_kind(prob,i,GLP_BV);

	}

	//Coefficients des variables dans la fonction objectif
	for(i = 1;i <= p.nbvar;i++) glp_set_obj_coef(prob,i,p.couts[i - 1]);

	//Remplissage de la matrice creuse des contraintes
	
	//On récupère le nombre de "creux" (de 1 en fait) de la matrice creuse
	nbcreux = 0;
	for(i = 0; i < p.nbcontr; i++) nbcreux += p.sizeContr[i];
	
	//Allocation mémoire pour les trois tableaux, ia, ja et ar pour la matrice creuse
	ia = (int *) malloc ((1 + nbcreux) * sizeof(int));
	ja = (int *) malloc ((1 + nbcreux) * sizeof(int));
	ar = (double *) malloc ((1 + nbcreux) * sizeof(double));

	//On remplit les tableaux
	pos = 1;
	for (i = 0; i < p.nbcontr; i++)
	{
		for(j = 0; j < p.sizeContr[i]; j++)
		{	
			//C'est comme dans le modèle explicite mais ici on gère directement 
			//les indices avec pos et le parcours dans sizeContr 
			ia[pos] = i + 1;
			ja[pos] = p.contr[i][j];
			ar[pos] = 1.0;
			pos++;
		}
	}

	//Chargement de la matrice dans le problème
	glp_load_matrix(prob,nbcreux,ia,ja,ar);

	////Ecriture de la résolution dans un fichier
	glp_write_lp(prob,NULL,"affect_machines.lp");

	//Résolution
	glp_simplex(prob,NULL);
	glp_intopt(prob,NULL);

	//Récupération du résultat
	z = glp_mip_obj_val(prob); //Valeur optimale
	x = (double *) malloc (p.nbvar * sizeof(double));
	for(i = 0;i < p.nbvar; i++) x[i] = glp_mip_col_val(prob,i+1); //Valeur de chaque variable

	//Affichage des résultats
	printf("z = %lf\n",z);
	for(i = 0;i < p.nbvar;i++) printf("x%c = %d, ",'B'+i,(int)(x[i] + 0.5));
	puts("");

	//Libération de la mémoire, problème prob et les tableaux
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

	//Fin 
	return 0;

} //Fermeture du main
