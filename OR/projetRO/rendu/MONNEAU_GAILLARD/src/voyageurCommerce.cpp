/* 
   GAILLARD Florent
   MONNEAU Dylan 
   601A
*/

#include "voyageurCommerce.hpp"

using namespace std;

int retrouverNumeroVariable(vector<string> v, char **numeroi, char **numeroj){
	string i = v[0];
	string j = v[1];
	int cpt = 0;
	while(i.compare(numeroi[cpt]) != 0)
		++cpt; // on avance dans le tableau contenant les noms des sommets i
	while(j.compare(numeroj[cpt]) != 0)
		++cpt; // puis on avance dans le tableau contenant les noms des sommets j
	return ++cpt; // on récupère l'indice auquel se trouve la variable (pour savoir à quelle colonne il se situe dans la matrice)
}

vector<vector<vector<string> > > sousTours(vector<vector<string> > v)
{
	// v contient l'ensemble des aretes impliqué dans un sous tours
	// Par exemple : 04 06 46 12 13 23

	vector<vector<vector<string> > > vSousTours; // on va pouvoir récupérer les sous tours
	vector<vector<string> > circuit; // ce sont les listes d'arêtes impliquées que l'on va "triées" selon le sous tours dans lesquels elles interviennent

	// tant que le vector passé en paramètre n'est pas vide
	while(v.size() != 0)
	{
		// on ajoute les derniers elements de v
		circuit.push_back(v[v.size()-1]);
		// on supprime les éléments que l'on vient d'ajouter
		v.pop_back();

		/* en gros, ces trois boucles permettent de savoir quels sont les autres aretes impliquées dans le sous tours
		dont déjà deux sommets ont été ajoutés au vector circuit */
		for(int i=0; i<circuit.size(); ++i)
		{
			for(int j=0; j<circuit[i].size(); ++j)
			{
				for(int k=0; k<v.size(); ++k)
				{
					// si un des sommets inclus dans v correspond avec un présent dans circuit
					// on l'ajoute aussi à circuit puis on le supprime de v
					if(v[k][0].compare(circuit[i][j]) == 0 || v[k][1].compare(circuit[i][j]) == 0)
					{
						circuit.push_back(v[k]);
						v.erase(v.begin()+k);
						--k;
					}
				}
			}
		}

		// ici, on a dans circuit, l'ensemble des aretes qui correspondent à UN sous tours
		// on peut donc les ajouter à notre vector de sous tours
		vSousTours.push_back(circuit);
		circuit.clear();
	}

	return vSousTours; // on retourne le vector à 3 dimensions qui distingue les sous tours entre eux
}

double* voyageurDuCommerce(vector<vector<int> > regroup, donnees p)
{
	glp_prob *prob; // définition du problème

	double *distancesMin; // tableau récupérant les résultats de la résolution du problème de TSP (toutes les distances minimum de chaque tournees possible) */	

	double *x; // les variables représentant les aretes d'un sommet i à un sommet j

	int *sizeContr; // représente la taille des contraintes
	int **contr; // permet de définir les numéros de colonnes de la matrice dans lequelles un 1 apparaitra
	
	// pour la matrice creuse
	int *lignes; 
	int *colonnes;
	double *valeurs;

	// pour le nom des variables
	char **nomvar; 
	char **numeroi;
	char **numeroj;
	
	// indices utilisés dans les boucles
	int i,j,k,m,n;

	// utilisé pour remplir les tableaux ou dans les fonctions glpk
	int cpt;
	int indice;

	int nbVar; // représente le nombre de variables
	int nbrContr; // représente le nombre de contraintes

	int nbcreux; // nombre d'éléments de la matrice creuse
	int pos; // compteur utilisé dans le remplissage de la matrice creuse

	vector<vector<string> > listeAretes; // récupère les aretes d'un sommet i à un sommet j impliqué dans un sous tours
	vector<vector<vector<string> > > listeSousTours; // récupère l'ensemble des sous tours
	vector<vector<int> > contraintesSousTours; // pour préserver les nouvelles contraintes à chaque fois que l'on rencontre un nouveau sous tours
	vector<int> numerosVar; // pour récupérer les numéros de colonnes impliquées dans les sous tours
	vector<int> tourneesPossible; // pour le regroupement possible analysé 

	distancesMin = (double *) malloc (regroup.size() * sizeof(double));

	for(k = 0; k<regroup.size(); ++k)
	{
		listeAretes.clear();
		listeSousTours.clear();
		contraintesSousTours.clear();

		// si la taille du regroupement analysé est de 1 alors il suffit de faire : la base -> point d'eau ; point d'eau -> la base 
		// soit 2 * la distance base <--> point d'eau
		if(regroup[k].size() == 1)
			distancesMin[k] = p.C[0][regroup[k][0]] * 2;
	
		// sinon, pour les regroupement de taille > 1
		else
		{
			// a chaque fois que l'on rencontre un sous tours
			do
			{
				// sauvegarde des contraintes de sous tours (on ne passera ici que s'il existe des sous tours)
				for (i = 0; i < listeSousTours.size(); ++i)
				{
					numerosVar.clear();
					for (j = 0; j < listeSousTours[i].size(); ++j)
					{
						numerosVar.push_back(retrouverNumeroVariable(listeSousTours[i][j],numeroi,numeroj));
					}
					contraintesSousTours.push_back(numerosVar);
				}

				prob = glp_create_prob(); /* allocation mémoire pour le problème */ 
				glp_set_prob_name(prob, "voyageurCommerce"); /* affectation du nom voyageur du commerce au probleme */
				glp_set_obj_dir(prob, GLP_MIN); /* Il s'agit d'un problème de minimisation */
				
				tourneesPossible = regroup[k]; // on affecte le regroupement analysé à un nom plus parlant

				// le nombre de contraintes 
				nbrContr = 2*(tourneesPossible.size() + 1) + contraintesSousTours.size(); 

				// le nombre de lignes de la matrice
				glp_add_rows(prob, nbrContr); 

				// les bornes de chaque contraintes du problème
				indice = 0;
				for(i=1; i<=nbrContr; ++i)
				{
					// pour le nombre de degre sortant et entrant de chaque sommet
					if(i <= (nbrContr-contraintesSousTours.size())/2)
						glp_set_row_bnds(prob, i, GLP_FX, 2.0, 2.0);
					// pour les sous tours de taille 1
					else if(i <= nbrContr-contraintesSousTours.size())
						glp_set_row_bnds(prob, i, GLP_FX, 0.0, 0.0);
					else
						glp_set_row_bnds(prob, i, GLP_DB, 0.0, contraintesSousTours[indice++].size()-1);
				}

				// le nombre de variables
				nbVar = ((tourneesPossible.size()+1) * (tourneesPossible.size() + 2)) / 2;   

				// le nombre de colonnes de la matrice
				glp_add_cols(prob, nbVar);

				// pour les noms des variables
				nomvar = (char **) malloc (nbVar * sizeof(char *)); // allocation mémoire pour le nom des variables
				numeroi = (char **) malloc (nbVar * sizeof(char *)); 
				numeroj = (char **) malloc (nbVar * sizeof(char *));  
				indice = 1;
				for(i=0; i<=tourneesPossible.size(); ++i)
				{
					for(j=i; j<=tourneesPossible.size(); ++j)
					{
						nomvar[indice-1] = (char *) malloc (5 * sizeof(char));
						numeroi[indice-1] = (char *) malloc (3  * sizeof(char)); 
						numeroj[indice-1] = (char *) malloc (3  * sizeof(char));

						// le nom de la base : x00
						if(i == 0 && j == 0)
						{
							sprintf(numeroi[indice-1], "%d", 0);
							sprintf(numeroj[indice-1], "%d", 0);
						}
						// les noms des variables où le sommet correspondant à la base est impliqué : x01, x02, ...
						else if(i == 0)
						{
							sprintf(numeroi[indice-1], "%d", 0);
							sprintf(numeroj[indice-1], "%d", tourneesPossible[j-1]);
						}
						else
						{
							sprintf(numeroi[indice-1], "%d", tourneesPossible[i-1]);
							sprintf(numeroj[indice-1], "%d", tourneesPossible[j-1]);	
						}

						strcpy(nomvar[indice-1],"x");
						strcat(nomvar[indice-1],numeroi[indice-1]); // nomvar[indice-1] contient "xi"
						strcat(nomvar[indice-1],","); // nomvar[indice-1] contient ","
						strcat(nomvar[indice-1],numeroj[indice-1]); // nomvar[indice-1] contient "xi,j"
						glp_set_col_name(prob, indice , nomvar[indice-1]); 

						glp_set_col_bnds(prob, indice, GLP_DB, 0.0, 1.0); // bornes sur les variables de 0 à 1
						glp_set_col_kind(prob, indice, GLP_BV);	// les variables sont binaires 

						++indice;
					}
				}

				// la fonction objectif
				cpt = 1;
				for(i=0; i<=tourneesPossible.size(); ++i)
				{
					for(j=i; j<=tourneesPossible.size(); ++j)
					{
						// pour la base
						if(i == 0 && j == 0)
							glp_set_obj_coef(prob, cpt, p.C[0][0]);
						// pour les sommets impliquant la base (la première ligne de la matrice dans le fichier de données)
						else if (i == 0)
							glp_set_obj_coef(prob, cpt, p.C[0][tourneesPossible[j-1]]);		
						else
							glp_set_obj_coef(prob, cpt, p.C[tourneesPossible[i-1]][tourneesPossible[j-1]]);
						
						++cpt;
					}
				}

				// définir la taille des contraintes
				sizeContr = (int *) malloc (nbrContr * sizeof(int));
				indice = 0;
				for(i=0; i<nbrContr; ++i)
				{
					if(i < (nbrContr-contraintesSousTours.size())/2)
						sizeContr[i] = tourneesPossible.size() + 1;
					// pour les sous tours de taille 1
					else if(i < nbrContr-contraintesSousTours.size())
						sizeContr[i] = 1;
					else
						sizeContr[i] = contraintesSousTours[indice++].size();
				}

				// définir le nombre de creux dans la matrice
				nbcreux = 0;
				for(i=0; i<nbrContr; ++i)
					nbcreux += sizeContr[i];

				lignes = (int *) malloc ((1 + nbcreux) * sizeof(int));
				colonnes = (int *) malloc ((1 + nbcreux) * sizeof(int));
				valeurs = (double *) malloc ((1 + nbcreux) * sizeof(double));

				contr = (int **) malloc (nbrContr * sizeof(int *));
				cpt = 1;

				m = 0;
				n = 0;
				
				// pour définir les numéros de colonnes (remplir le tableau contr[i][j]) 
				for(i=0; i<nbrContr; ++i)
				{
					contr[i] = (int *) malloc (sizeContr[i] * sizeof(int));

					for(j=0; j<sizeContr[i]; ++j)
					{
						// pour les n/2 premières contraintes
						if(i < (nbrContr-contraintesSousTours.size())/2)
						{	
							// concernant la ligne de la base (où elle intervient dans la matrice)
							if(i == 0)
								contr[i][j] = j+1;
							// pour les autres sommets
							else
							{
								// on ajoute 1 au résultat de la ligne précédente pour les colonnes < i
								if(j < i)
									contr[i][j] = contr[i-1][j] + 1;
								// sinon le résultat dépend toujours de la ligne précédente mais on ajoute la taille du regroupement - i
								else 
									contr[i][j] = contr[i-1][j] + tourneesPossible.size() + 1 - i;      
							}
						}
						// pour les sous tours de 1 --> x00 = 0
						else if(i < nbrContr-contraintesSousTours.size())
						{
							// concernant la ligne de la base (00 --> colonne 1)
							if(i == (nbrContr-contraintesSousTours.size())/2)
								contr[i][j] = 1;
							// pour les sous tours des autres sommets, on dépend de la colonne du sommet précédent
							else
							{	
								contr[i][j] = contr[i-1][j] + i - cpt;   
								cpt += 2;
							}
						}
						else
						{	
							contr[i][j] = contraintesSousTours[m][n];
							n++;
							if (n == contraintesSousTours[m].size()){
								m++;
								n=0;
							}
						}
					}
				}
				
				// on remplit la matrice
				pos = 1;
				for(i = 0; i < nbrContr;i++)
				{
					for(j = 0;j < sizeContr[i];j++)
					{
						lignes[pos] = i + 1;
						colonnes[pos] = contr[i][j];
						valeurs[pos] = 1.0; 
						pos++;
					}
				}

				glp_term_out(GLP_OFF); // ne pas afficher la sortie terminal de GLPK

				glp_load_matrix(prob,nbcreux,lignes,colonnes,valeurs); // on charge le problème dans la matrice

				glp_simplex(prob,NULL);	glp_intopt(prob,NULL); /* Résolution */

				distancesMin[k] = glp_mip_obj_val(prob); /* Récupération de la valeur optimale. */
			
				// récupération des valeurs des variables
				x = (double *) malloc (nbVar * sizeof(double));
				for(i = 0;i < nbVar; i++) 
					x[i] = glp_mip_col_val(prob,i+1);

				// pour l'ensemble des variables à 1 (les aretes par lesquelles passent le drone)
				for(i = 0;i < nbVar;i++) 
					if((int)(x[i] + 0.5) != 0)
					{
						vector<string> aretes;
						aretes.push_back(numeroi[i]);
						aretes.push_back(numeroj[i]);
						listeAretes.push_back(aretes);
					}

				// on regarde s'il existe des sous tours
				listeSousTours = sousTours(listeAretes);

			} while(listeSousTours.size() > 1); // si ce vector a une taille > 1, c'est qu'il existe des sous tours
		} 
	}

	return distancesMin; // on retourne le tableau des distances minimum à parcourir pour l'ensemble des regroupements possibles
}