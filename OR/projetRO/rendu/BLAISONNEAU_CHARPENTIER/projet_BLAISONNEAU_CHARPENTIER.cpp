#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h>
#include <vector>
#include <math.h>

//PROJET BLAISONNEAU CHARPENTIER
//Nous n'avons pas utilis� le .c fourni, nous nous en somme rendu compte trop tard. Nous nous excusons.

using namespace std;

typedef struct 
{
	int nb_sources;
	int capacite_drone;
	int *volume_eau;
	int **matrice_distances;
}donnees_map;

typedef struct 
{
	int longueur_opti;
	int *sommets;
	int nb_sommets;
}donnees_circuit;

typedef struct
{
	vector<donnees_circuit> circuits;
	int nb_circuits;
}liste_de_donnees_circuits;

typedef struct
{
	int *sommets;
	int nb_sommets;
}sous_circuit;

typedef struct
{
	sous_circuit *sous_circuits;
	int nb_sous_circuits;
}liste_de_sous_circuits;

void remplir_donnes_map(char *nomfich, donnees_map *don)
{
	FILE *fichier;
	int i,j;	
	int tmp;
	
	fichier = fopen(nomfich,"r"); 
	fscanf(fichier, "%d", &tmp);
	don->nb_sources = tmp;
	fscanf(fichier, "%d", &tmp);
	don->capacite_drone = tmp;
	don->volume_eau = (int *) malloc(don->nb_sources * sizeof(int));
	don->matrice_distances = (int **) malloc(don->nb_sources * sizeof(int*));
	
	for(i = 0 ; i < don->nb_sources - 1; ++i)
	{
		fscanf(fichier, "%d", &tmp);
		don->volume_eau[i] = tmp;
	}
	
	for(i = 0 ; i < don->nb_sources ; ++i)
	{
		don->matrice_distances[i] = (int *) malloc(don->nb_sources * sizeof(int));
		for(j = 0 ; j < don->nb_sources ; ++j)
		{
			fscanf(fichier, "%d", &tmp);
			don->matrice_distances[i][j] = tmp;
		}
	}
	fclose(fichier);
}

int indice_arc(int indice_origine, int indice_destination, int nbsommets)
{
	int n = nbsommets;
	int a = indice_origine;
	int b = indice_destination;
	//printf("calcul de ind ( %d, %d, %d )", a,b,n);
	//printf("mystere = %d - % d + % d\n", ((n)*(n+1))/2  , ((n-a+1) * (n-a)) / 2, b-a);
	return(((n)*(n+1))/2 - ((n-a) * (n-a+1)) / 2 + (b - a));
}

long deux_puissance_x(long i)
{
	long tmp;
	
	tmp = 1;
	while(i > 0)
	{
		tmp = tmp * 2;
		i--;
	}
	return(tmp);
}

int	check_circuit_realisable(donnees_map map, donnees_circuit sous_circ)
{
	int tmp;
	int i;
	tmp = 0;
	for(i = 0 ; i < sous_circ.nb_sommets ; ++i)
	{
		tmp += map.volume_eau[sous_circ.sommets[i] - 1];
	}
	return(tmp > map.capacite_drone ? 0 : 1);
}

void liste_des_sous_ensembles(liste_de_sous_circuits *liste, int indice, sous_circuit sous_circ, int sterile_call, donnees_circuit reseau_original)
{
	if(indice == 0) // indice est le numéro de la source qu'on ajoute (ou pas) au circuit pour cet appel
	{
		liste->sous_circuits = (sous_circuit *) malloc(deux_puissance_x(reseau_original.nb_sommets) * sizeof(sous_circuit));
		liste->nb_sous_circuits = 0;
	}
	if(indice <= reseau_original.nb_sommets)
	{
		if(sterile_call != 1 && sous_circ.nb_sommets > 0 && sous_circ.nb_sommets < reseau_original.nb_sommets) // sterile_call == 1 signifie que l'on n'a pas ajouté la source a l'appel parent, et donc ce circuit est déjà présent dans la liste
		{
			liste->sous_circuits[liste->nb_sous_circuits] = sous_circ;
			liste->nb_sous_circuits++;
		}
		
		sous_circuit copie;
		int i;
		
		copie.nb_sommets = sous_circ.nb_sommets + 1;
		copie.sommets = (int *) malloc((sous_circ.nb_sommets + 1) * sizeof(int));
		for(i = 0; i < sous_circ.nb_sommets ; ++i)
		{
			copie.sommets[i] = sous_circ.sommets[i];
		}
		copie.sommets[copie.nb_sommets - 1] = reseau_original.sommets[indice];
		liste_des_sous_ensembles(liste, indice + 1, copie, 0, reseau_original); // copie est different, ainsi cet appel n'est pas stérile.
		liste_des_sous_ensembles(liste, indice + 1, sous_circ, 1, reseau_original); // sous_circuit n'a pas change , donc cet appel est sterile
	}
}

void complementaire_a_en_fct_de_b(sous_circuit origin, donnees_circuit refer, sous_circuit *ret)
{
	int i;
	int j;
	
	j = 0;
	
	ret->nb_sommets = 0;
	ret->sommets = (int *)malloc((refer.nb_sommets - origin.nb_sommets) * sizeof(int));
	for(i = 0 ; i < refer.nb_sommets ; ++i)
	{
		if(origin.sommets[j] != refer.sommets[i])
		{
			ret->sommets[ret->nb_sommets] = refer.sommets[i];
			ret->nb_sommets++;
		}
		else if(j<origin.nb_sommets - 1)
		{
			j++;
		}
	}
	/*printf("ceci est un ensemble : ");
	for(i = 0; i < origin.nb_sommets; ++i)
	{
			printf("%d ", origin.sommets[i]);
	}
	printf("\n\n");
	
	printf("ceci est un complementaire : ");
	for(i = 0; i < ret->nb_sommets; ++i)
	{
			printf("%d ", ret->sommets[i]);
	}
	printf("\n\n");*/
}

void calculer_longueur_opti(donnees_circuit *donnees_circ, donnees_map map)
{
	glp_prob *prob;
	
	int *ia;
	int *ja;
	double *ar;
	int pos;
	
	int i;
	int j;
	int k;
	int l;
	
	int indcontr;
	
	int nbcol;

	int nblig;
	
	int distance_opti;
	
	
	sous_circuit tmp;

	liste_de_sous_circuits sous_sous_circuits;
	liste_de_sous_circuits complementaires;
	
	if(donnees_circ->nb_sommets == 1)
	{
		donnees_circ->longueur_opti = 2 * map.matrice_distances[0][donnees_circ->sommets[0]];
	}
	else if(donnees_circ->nb_sommets == 2)
	{
		donnees_circ->longueur_opti = map.matrice_distances[0][donnees_circ->sommets[0]] + map.matrice_distances[0][donnees_circ->sommets[1]]
																							+ map.matrice_distances[donnees_circ->sommets[0]][donnees_circ->sommets[1]];
	}
	else
	{
		tmp.nb_sommets = 0;
		tmp.sommets = (int *) malloc((1 + donnees_circ->nb_sommets) * sizeof(int));
		
		donnees_circuit dude;
		dude.sommets = (int *)malloc(((1+donnees_circ->nb_sommets) *sizeof(int)));
		dude.nb_sommets = donnees_circ->nb_sommets + 1;
		for(i = 0 ; i <= donnees_circ->nb_sommets ; ++i)
		{
			dude.sommets[i] = i;
		}

		
		liste_des_sous_ensembles(&sous_sous_circuits, 0, tmp, 0, dude);
		
		complementaires.sous_circuits = (sous_circuit*)malloc(sous_sous_circuits.nb_sous_circuits * sizeof(sous_circuit));
		complementaires.nb_sous_circuits = sous_sous_circuits.nb_sous_circuits;
		
		for(i = 0 ; i < sous_sous_circuits.nb_sous_circuits ; ++i)
		{
			complementaires.sous_circuits[i].nb_sommets = map.nb_sources - sous_sous_circuits.sous_circuits[i].nb_sommets;
			complementaire_a_en_fct_de_b(sous_sous_circuits.sous_circuits[i], dude, &complementaires.sous_circuits[i]);
		}
	
		// n est ici le nombre de sommets du graphe privé de la source
		//variables de décision : arcs. le graphe est connexe donc on en a n * (n-1) / 2 (les arcs sont non-orientés par souci de simplification car dans ce problème les distances sont les memes en aller et retour
		//les variables de décision sont sur un vecteur, ce qui rend leur numérotation très énervante. Peut etre faire une fonction qui fait la bijection a-b -> numéro de la contrainte ??
		//contraintes :
					//	chaque sous groupe doit avoir au moins deux arcs entre un de ses éléments et un de ses non - éléments.
					// 	cela fait 2^(nombre de sommets) contraintes, car on exclut le sous ensemble vide
					//  il s'agit des sous ensembles de sommets non-base mais cela est suffisant car si l'on assure qu'il n'y a pas de cycles dans cet ensemble et qu'il est relié à la base
					//  on peut affirmer que l'ensemble entier est sans boucle (impossibilité de boucler sur soi)
					
		prob = glp_create_prob();
		glp_set_obj_dir(prob, GLP_MIN);
		glp_set_prob_name(prob, "voyageur de commerce non orienté");
		

		nbcol =  ((donnees_circ->nb_sommets + 1) * ( donnees_circ->nb_sommets) ) / 2;
		nblig =  sous_sous_circuits.nb_sous_circuits;
		
		//printf("col, lig : %d %d",nbcol, nblig);

		glp_add_cols(prob, nbcol); // nombre d'arcs non orientés dans un graphe connexe contenant 1 + le nombre de sommets dans le sous-ensemble passé
		
		glp_add_rows(prob, nblig);
		
		indcontr = 1;
			
		for(i = 1 ; i <= nblig; ++i) // contraintes d'entrée/sortie des ensembles >= 2
		{
			glp_set_row_bnds(prob, indcontr, GLP_LO, 2.0, 3.0);
			indcontr++;
		} 
		
		////////:
		////////
		
		//fonction objectif
		for(i = 1 ; i <= donnees_circ->nb_sommets; ++i)
		{
			glp_set_obj_coef(prob,i,map.matrice_distances[0][donnees_circ->sommets[i-1]]);;
			//printf("indice %d distance %d \n", i,map.matrice_distances[0][donnees_circ->sommets[i-1]]);
			glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0);
			glp_set_col_kind(prob, i, GLP_BV);
		}
		for(i = 1 ; i < donnees_circ->nb_sommets; ++i)
		{
			for(j = i + 1 ; j <= donnees_circ->nb_sommets; ++j)
			{
				//printf("ceci est un indice(bis) : %d et voici sa distance associée : %d \n",indice_arc(i ,j ,donnees_circ->nb_sommets), map.matrice_distances[donnees_circ->sommets[i-1]][donnees_circ->sommets[j-1]]);
				glp_set_obj_coef(prob,indice_arc(i ,j ,donnees_circ->nb_sommets), map.matrice_distances[donnees_circ->sommets[i-1]][donnees_circ->sommets[j-1]]);
				glp_set_col_bnds(prob, indice_arc(i ,j ,donnees_circ->nb_sommets), GLP_DB, 0.0, 1.0);
				glp_set_col_kind(prob, indice_arc(i ,j ,donnees_circ->nb_sommets), GLP_BV);
			}
		}
		
		ia = (int *)malloc((1 + nbcol * nblig) * sizeof(int));
		ja = (int *)malloc((1 + nbcol * nblig) * sizeof(int));
		ar = (double *)malloc((1 + nbcol * nblig) * sizeof(double));
		
	
		indcontr = 1;
		
						
		for(i = 0; i < sous_sous_circuits.nb_sous_circuits; ++i)//ieme contrainte ieme sous circuit
		{
			for(k = 0; k < sous_sous_circuits.sous_circuits[i].nb_sommets; k++)
			{
				for(l = 0; l < complementaires.sous_circuits[i].nb_sommets; l++)
				{
					ia[indcontr] = i + 1;
					ar[indcontr] = 1.0;
					if(sous_sous_circuits.sous_circuits[i].sommets[k] < complementaires.sous_circuits[i].sommets[l])
						ja[indcontr] = indice_arc(sous_sous_circuits.sous_circuits[i].sommets[k], complementaires.sous_circuits[i].sommets[l], donnees_circ->nb_sommets);
					else
						ja[indcontr] = indice_arc(complementaires.sous_circuits[i].sommets[l], sous_sous_circuits.sous_circuits[i].sommets[k], donnees_circ->nb_sommets);
					indcontr++;
				}
			}
		}

		

		glp_load_matrix(prob, indcontr - 1, ia, ja, ar);
		glp_simplex(prob, NULL); glp_intopt(prob,NULL);
		
		donnees_circ->longueur_opti = (int) (glp_mip_obj_val(prob) + 0.5);
		
		free(ia);free(ja);free(ar);free(tmp.sommets);free(dude.sommets);
	}
}


void	add_circ(int *permut, int nbsom, liste_de_donnees_circuits *list_donnees,donnees_map map)
{
	donnees_circuit tmp = donnees_circuit();
	tmp.nb_sommets = 0;
	tmp.longueur_opti = 0;
	tmp.sommets = (int *)malloc((map.nb_sources - 1)* sizeof(int));
	
	for(int i = 0 ; i < map.nb_sources -1 ; ++i)
	{
		if(permut[i] != 0)
		{
			tmp.sommets[tmp.nb_sommets] = permut[i];
			tmp.nb_sommets++;
		}
	}
	
	//calculer_longueur_opti(&tmp, map);
	
	list_donnees->circuits.push_back(tmp);
	list_donnees->nb_circuits++;

}




void remplir_liste_donnees_circuits2(liste_de_donnees_circuits *list_donnees, donnees_map map)
{
	int tmp;
	int nbsom;
	int indice = 0;
	int *permut = (int *)malloc(map.nb_sources *sizeof(int));
	
	int nbsources = map.nb_sources;
	long end = pow(2,map.nb_sources - 1);
	
	for(int i = 0; i < map.nb_sources - 1 ; ++i)
	{
		permut[i] = 0;
	}
	
	//for (int k = 0 ; k < map.nb_sources - 1; ++k)printf("%d ", permut[k]);
	
	
	for(long i = 0; i < end; ++i)
	{
		/*
		tmp = 0;
		nbsom = 0;
		for(int j = 0; j < nbsources - 1; ++j)
		{
			if(i % deux_puissance_x(j) == 0)
			{
				if(permut[j] == 0) permut[j] = j + 1;
				else permut[j] = 0;
			}
		}
		
		for(int j = 0; j < nbsources - 1; ++j)
		{
			tmp += ((permut[j] == 0) ? 0 : 1) * map.volume_eau[j];
			nbsom += permut[j];
			//printf("%d ", permut[j]);
		}
		if(tmp <= map.capacite_drone && nbsom != 0)
		{
			add_circ(permut, nbsom, list_donnees, map);
		}
		*/
	}
}

void remplir_liste_donnees_circuits(liste_de_donnees_circuits *list_donnees, donnees_map map, int indice, donnees_circuit sous_circ, int sterile_call)
{
	
	donnees_circuit copie;
	int i;
		
	copie.nb_sommets = sous_circ.nb_sommets + 1;
	copie.longueur_opti = 0;
	copie.sommets = (int *) malloc((sous_circ.nb_sommets + 1 )* sizeof(int));
	for(i = 0; i < sous_circ.nb_sommets ; ++i)
	{
		copie.sommets[i] = sous_circ.sommets[i];
		printf("%d " , sous_circ.sommets[i]);
	}
	printf("\n");
	copie.sommets[copie.nb_sommets - 1] = indice + 1;
	
	
	if(indice == 0) // indice est le numéro de la source qu'on ajoute (ou pas) au circuit pour cet appel
	{
	}
	if(indice < map.nb_sources)
	{
		if(sous_circ.nb_sommets > 0) // sterile_call == 1 signifie que l'on n'a pas ajouté la source a l'appel parent, et donc ce circuit est déjà présent dans la liste
		{													//et aussi on refuse un circuit de longueur 0...
			if(check_circuit_realisable(map, sous_circ) ==  1)
			{
				if(sterile_call == 0)
				{
					calculer_longueur_opti(&sous_circ, map);
					list_donnees->circuits.push_back(sous_circ);
					list_donnees->nb_circuits++;
				}
				copie.sommets[copie.nb_sommets - 1] = indice + 1;
				remplir_liste_donnees_circuits(list_donnees, map, indice + 1, copie, 0); // copie est different, ainsi cet appel n'est pas stérile.
				remplir_liste_donnees_circuits(list_donnees, map, indice + 1, sous_circ, 1); // donnees_circuit n'a pas change , donc cet appel est sterile
			}
		}
		else
		{
			remplir_liste_donnees_circuits(list_donnees, map, indice + 1, copie, 0); // copie est different, ainsi cet appel n'est pas stérile.
			remplir_liste_donnees_circuits(list_donnees, map, indice + 1, sous_circ, 1); // donnees_circuit n'a pas change , donc cet appel est sterile
		}
		
		//~ donnees_circuit copie;
		//~ int i;
		//~ 
		//~ copie.nb_sommets = sous_circ.nb_sommets + 1;
		//~ copie.longueur_opti = 0;
		//~ copie.sommets = (int *) malloc((sous_circ.nb_sommets + 1 )* sizeof(int));
		//~ for(i = 0; i < sous_circ.nb_sommets ; ++i)
		//~ {
			//~ copie.sommets[i] = sous_circ.sommets[i];
		//~ }
		//~ copie.sommets[copie.nb_sommets - 1] = indice + 1;
		//~ remplir_liste_donnees_circuits(list_donnees, map, indice + 1, copie, 0); // copie est different, ainsi cet appel n'est pas stérile.
		//~ remplir_liste_donnees_circuits(list_donnees, map, indice + 1, sous_circ, 1); // donnees_circuit n'a pas change , donc cet appel est sterile
		//~ //free(copie.sommets);
	}
}

int nb_circuits_ok(donnees_map map, int indice, donnees_circuit sous_circ, int sterile_call)
{
	int ret;
	ret = 0;
	if(indice < map.nb_sources)
	{
		if(sterile_call == 0 && check_circuit_realisable(map, sous_circ) ==  1)
			ret++;
		
		ret += nb_circuits_ok(map, indice + 1, sous_circ, 1);
		
		sous_circ.sommets[sous_circ.nb_sommets] = indice;
		sous_circ.nb_sommets++;
		
		ret += nb_circuits_ok(map, indice + 1, sous_circ, 0);
		
		return(ret);
	}
	else
		return 0;
}


int partitionnement(liste_de_donnees_circuits *data, int nb_sources)
{
	glp_prob *prob;
	
	int *ia;
	int *ja;
	double *ar;
	int pos;
	
	int i;
	int j;
	int nbcreux;
	
	prob = glp_create_prob();
	
	glp_set_prob_name(prob, "partitionnement d'ensemble");
	glp_set_obj_dir(prob, GLP_MIN);
	
	glp_add_rows(prob, nb_sources - 1);
	
	for(i = 1 ; i <= nb_sources - 1 ; ++i)
	{
		glp_set_row_bnds(prob, i, GLP_FX, 1.0, 1.0);
	}
	
	glp_add_cols(prob, data->nb_circuits);
	
	for(i = 1 ; i <= data->nb_circuits ; ++i)
	{
		glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0);
		glp_set_col_kind(prob, i, GLP_BV);	
	}
	
	for(i = 1 ;  i <= data->nb_circuits ; ++i)
	{
		 glp_set_obj_coef(prob,i,data->circuits[i-1].longueur_opti);
	}
	
	nbcreux = 0;
	
	for(i = 0 ;  i < data->nb_circuits ; ++i)
	{
		 nbcreux += data->circuits[i].nb_sommets;
	}
	
	ia = (int *) malloc ((1 + nbcreux) * sizeof(int));
	ja = (int *) malloc ((1 + nbcreux) * sizeof(int));
	ar = (double *) malloc ((1 + nbcreux) * sizeof(double));
	
	pos = 1;
	for(i = 0 ; i < data->nb_circuits ; ++i)
	{
		for(j = 0 ; j < data->circuits[i].nb_sommets; j++)
		{
			ia[pos] = data->circuits[i].sommets[j];
			ja[pos] = i + 1;
			ar[pos] = 1.0;
			pos++;
		} 
	}
	
	glp_load_matrix(prob, pos - 1, ia, ja, ar);
	glp_write_lp(prob,NULL,"voyageur-commerce.lp");
	glp_simplex(prob, NULL); glp_intopt(prob,NULL);
	
		printf("LA SOLUTION DE LA FIN : %d \n EN PRENANT LES CIRCUITS :", (int) (0.5 + glp_mip_obj_val(prob)));
	for(i = 0; i <  data->nb_circuits ; ++i)
	{
		if(glp_mip_col_val(prob,i+1) == 1.0)
		{
			printf(" %d", i);
		}
	}
	printf("\n\n");
	
	
	return((int) (0.5 + glp_mip_obj_val(prob)));
	

}

int main(int argc, char *argv[])
{	
	donnees_map don;
	liste_de_donnees_circuits list_donnees;
	donnees_circuit sous_circ;
	int nb_circ;
	int resultat;
	
	remplir_donnes_map(argv[1], &don);
		
	sous_circ.nb_sommets = 0;
	sous_circ.sommets = (int *) malloc(don.nb_sources * sizeof(int));
	sous_circ.longueur_opti = 0;
	
	//nb_circ = nb_circuits_ok(don, 1, sous_circ, 0);
	
	glp_term_out(GLP_OFF);
	free(sous_circ.sommets);
	
	sous_circ.sommets = (int *) malloc(don.nb_sources * sizeof(int));
	sous_circ.nb_sommets = 0;
	sous_circ.sommets[0] = 1;
	
	list_donnees.nb_circuits = 0;
	
	remplir_liste_donnees_circuits(&list_donnees, don, 0, sous_circ, 0);
	//remplir_liste_donnees_circuits2(&list_donnees, don);
	resultat = partitionnement(&list_donnees, don.nb_sources);
	long i;
	long j;
	
	for(i = 0; i < don.nb_sources; ++i)
	{
		for(j = 0; j < don.nb_sources; ++j)
		{
			printf("%d ", don.matrice_distances[i][j]);
		}
		printf("\n");
	}
	
	for(i = 0; i < list_donnees.nb_circuits ; ++i)
	{
		printf("%ld : ", i);
		for(j = 0; j < list_donnees.circuits[i].nb_sommets; ++j)
		{
			printf("%d ", list_donnees.circuits[i].sommets[j]);
		}
		
		printf(" -- %d\n", list_donnees.circuits[i].longueur_opti);
	}
	printf("r�sultat final : %d\n", resultat);
	return 0;
}
