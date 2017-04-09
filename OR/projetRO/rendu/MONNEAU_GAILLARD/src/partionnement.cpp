/* 
   GAILLARD Florent
   MONNEAU Dylan 
   601A
*/
#include "partionnement.hpp"

using namespace std;

int nbTournee(vector<vector<int> > regroup, int x) 
{
	int cpt = 0;

	// permet de compter le nombre de tournées incluant le point de pompage x
	for(int i=0; i<regroup.size(); ++i)
		for(int j=0; j<regroup[i].size(); ++j)
			if(regroup[i][j] == x)
				++cpt;

	return cpt;
}

vector<int> tourneesPresente(vector<vector<int> > regroup, int x)
{
	vector<int> indiceTournees;

	// permet de récupérer l'ensemble des numéros de tournées incluant le point de pompage x
	for(int i=0; i<regroup.size(); ++i)
		for(int j=0; j<regroup[i].size(); ++j)
			if(regroup[i][j] == x)
				indiceTournees.push_back(i+1);

	return indiceTournees;
}

void partionnementTournees(vector<vector<int> > regroup, double* distancesMin, donnees p)
{
	glp_prob *prob;

	/* variables récupérant les résultats de la résolution du problème de partitionnement (fonction objectif et valeur des variables) */
	double *x; 
	double z;

	int *sizeContr; // représente la taille des contraintes

	// pour la matrice creuse
	int *lignes;
	int *colonnes;
	double *valeurs;

	// pour le nom des variables
	char **nomvar; 
	char **numeroi;

	int i,j; // indices utilisés dans les boucles
	
	int nbVar; // représente le nombre de variables
	int nbrContr; // représente le nombre de contraintes

	int nbcreux; // nombre d'éléments de la matrice creuse
	int pos; // compteur utilisé dans le remplissage de la matrice creuse
	
	vector<int> tournees; // pour récupérer les nuémros de colonnes liés à une tournée donnée 

	prob = glp_create_prob(); /* allocation mémoire pour le problème */ 
	glp_set_prob_name(prob, "Partitionnement"); /* affectation du nom patitionnement au probleme */
	glp_set_obj_dir(prob, GLP_MIN); /* Il s'agit d'un problème de minimisation */
	
	// le nombre de contraintes
	nbrContr = p.nblieux - 1;

	// nombre de colonnes de la matrice
	glp_add_rows(prob, nbrContr);

	// borne pour les contraintes
	for(i=1; i<=nbrContr; ++i)
	{
		glp_set_row_bnds(prob, i, GLP_FX, 1.0, 1.0);
	}

	// le nombre de variables
	nbVar = regroup.size();

	// nombre de lignes de la matrice
	glp_add_cols(prob, nbVar);

	// pour le noms des variables
	numeroi = (char **) malloc (nbVar * sizeof(char *)); 
	nomvar = (char **) malloc (nbVar * sizeof(char *));
	for(i=1; i<=nbVar; ++i)
	{
		nomvar[i-1] = (char *) malloc (5 * sizeof(char));
		numeroi[i-1] = (char *) malloc (3  * sizeof(char)); 

		sprintf(numeroi[i-1], "%d", i);

		strcpy(nomvar[i-1],"x");
		strcat(nomvar[i-1], numeroi[i-1]);
		glp_set_col_name(prob, i , nomvar[i-1]);

		glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0); // bornes sur les variables de 0 à 1
		glp_set_col_kind(prob, i, GLP_BV);	// les variables sont binaires 
	}

	// la fonction objectif
	for(i=1; i<=nbVar; ++i)
		glp_set_obj_coef(prob, i, distancesMin[i-1]);

	// définir la taille des contraintes
	sizeContr = (int *) malloc (nbrContr * sizeof(int));
	for(i=0; i<nbrContr; ++i)
			sizeContr[i] = nbTournee(regroup, i+1);

	// définir le nombre de creux dans la matrice
	nbcreux = 0;
	for(i=0; i<nbrContr; ++i)
		nbcreux += sizeContr[i];

	// remplir la matrice
	lignes = (int *) malloc ((1 + nbcreux) * sizeof(int));
	colonnes = (int *) malloc ((1 + nbcreux) * sizeof(int));
	valeurs = (double *) malloc ((1 + nbcreux) * sizeof(double));
	pos = 1;
	for(i = 0; i < nbrContr;++i)
	{
		tournees = tourneesPresente(regroup, i+1);
		for(j = 0;j < sizeContr[i];++j)
		{
			lignes[pos] = i + 1;
			colonnes[pos] = tournees[j];
			valeurs[pos] = 1.0; 
			pos++;
		}
	}

	// on affiche la sortie terminal de GLPK
	glp_term_out(GLP_ON);

	// on charge le problème dans la matrice
	glp_load_matrix(prob,nbcreux,lignes,colonnes,valeurs); 

	// on écrit la modélisation du problème dans un fichier
	glp_write_lp(prob,NULL,"partionnement.lp");

	glp_simplex(prob,NULL);	glp_intopt(prob,NULL); /* Résolution */

	// récupération des résultats
	z = glp_mip_obj_val(prob); 
	x = (double *) malloc (nbVar * sizeof(double));
	for(i = 0;i < nbVar; i++) x[i] = glp_mip_col_val(prob,i+1);

	// Affichage
	printf("z = %lf\n",z);
	for(i = 0;i < nbVar;i++) 
		if((int)(x[i] + 0.5) != 0)
		{
			printf("%s = ",nomvar[i]);
			printf("(");
			for(j=0; j<regroup[i].size(); ++j)
				printf(" %d ", regroup[i][j]);
			printf(") --> distance min : %lf \n", distancesMin[i]);
		}
}