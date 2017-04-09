/* SALAUN Nathan
   BOUDINE Alexandre */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h> /* Bibliothèques utilisées pour mesurer le temps CPU */

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef vector< vector<int>* >* regroupements;


void regroupement_print(vector<int>* subList)
{
    for (int j = 0; j < subList->size(); j++)
    {
        cout << subList->at(j) << ", ";
    }
}


void regroupements_print(regroupements list)
{
    for (int i = 0; i < list->size(); i++)
    {
        vector<int>* subList = list->at(i);
        regroupement_print(subList);
        cout << endl;
    }
}

regroupements regroupements_create(int n, const int c, int* v)
{
    regroupements list = new vector< vector<int>* >();
    vector<int> capacites = vector<int>();
    
    //Création de la liste de base
    for (int i = 1; i <= n; i++)
    {
        vector<int>* tmp = new vector<int>();
        
        tmp->push_back(i);
        list->push_back(tmp);
        
        capacites.push_back(v[i]);
    }
    
    //On itère sur chaque regroupement pour le copier et y ajouter les éléments suivants
    for (int i = 0; i < list->size(); i++)
    {
        int j = (list->at(i)->at(list->at(i)->size()-1));
        
        if (j < n) //si le regroupement n'est pas déjà terminé
        {   
            vector<int>* base = list->at(i);
            
            int capaciteBase = capacites[i];
            
            for (int k = j+1; k <= n; k++)
            {
                int capacite = capaciteBase + v[k];

                if (capacite <= c) //si le regroupement ne dépasse pas la capacité du drône
                {
                    vector<int>* tmp2 = new vector<int>();

                    tmp2->insert(tmp2->end(), base->begin(), base->end());
                    tmp2->push_back(k);
                    list->push_back(tmp2);
                    capacites.push_back(capacite);
                }
            }
        }
    }
    
    return list;
}

void regroupements_free(regroupements list)
{
    for (int i = 0; i < list->size(); i++)
    {
        vector<int>* subList = list->at(i);
        delete subList;
    }
    
    delete list;
}

//calcul du coût (distance) d'un regroupement
int get_cost(vector<int>* regroupement, int** cv, int cc)
{
    int res = 0;
    
    vector<int> tmp;
    tmp.insert(tmp.end(), regroupement->begin(), regroupement->end());

    tmp.insert(tmp.begin(), 0);
    tmp.push_back(0);
    
    for (int i = 0; i < tmp.size()-1; i++)
    {
        res += cv[tmp.at(i)][tmp.at(i+1)];
    }
    
    return res;
}

//calcul du coût minimum d'un regroupement (permutations)
int regroupement_get_cout_minimum(vector<int>* regroupement, int** cv, int cc)
{    
    int cost = get_cost(regroupement, cv, cc);
    
    do
    {
        int tmp = get_cost(regroupement, cv, cc);
        if (tmp < cost)
            cost = tmp;
    }
    while (next_permutation(regroupement->begin(), regroupement->end()));
    
    return cost;
}   

/* structures et fonctions de mesure du temps CPU */

struct timeval start_utime, stop_utime;

void crono_start()
{
	struct rusage rusage;
	
	getrusage(RUSAGE_SELF, &rusage);
	start_utime = rusage.ru_utime;
}

void crono_stop()
{
	struct rusage rusage;
	
	getrusage(RUSAGE_SELF, &rusage);
	stop_utime = rusage.ru_utime;
}

double crono_ms()
{
	return (stop_utime.tv_sec - start_utime.tv_sec) * 1000 +
    (stop_utime.tv_usec - start_utime.tv_usec) / 1000 ;
}

/* Structure contenant les données du problème */

typedef struct {
	int nblieux; /* Nombre de lieux (incluant le dépôt) */
	int capacite; /* Capacité du véhicule de livraison */
	int *demande; /* Demande de chaque lieu (la case 0 est inutilisée car le dépôt n'a aucune demande à voir satisfaire) */
	int **C; /* distancier (les lignes et colonnes 0 correspondent au dépôt) */
} donnees;

/* lecture des donnees */

void lecture_data(char *file, donnees *p)
{
	int i,j;
	FILE *fin;
	
	int val;
	fin = fopen(file,"rt");
	
	/* Lecture du nombre de villes */
	
	int osef = fscanf(fin,"%d",&val);
	p->nblieux = val;

	/* Allocation mémoire pour la demande de chaque ville, et le distancier */
	
	p->demande = (int *) malloc (val * sizeof(int));
	p->C = (int **) malloc (val * sizeof(int *));
	for(i = 0;i < val;i++) p->C[i] = (int *) malloc (val * sizeof(int));
	
	/* Lecture de la capacité */
	
	osef = fscanf(fin,"%d",&val);
	p->capacite = val;
	
	/* Lecture des demandes des clients */
	
	for(i = 1;i < p->nblieux;i++)
	{
		osef = fscanf(fin,"%d",&val);
		p->demande[i] = val;
	}
	
	/* Lecture du distancier */

	for(i = 0; i < p->nblieux; i++)
		for(j = 0; j < p->nblieux; j++)
		{
			int osef = fscanf(fin,"%d",&val);
			p->C[i][j] = val;
		}
		
	fclose(fin);
}

/* Fonction de libération mémoire des données */

void free_data(donnees *p)
{
	int i;
	for(i = 0;i < p->nblieux;i++) free(p->C[i]);
	free(p->C);
	free(p->demande);	
}

//Nombre de tournées ou apparait x
int nbApparitions(regroupements tourns, int x) {
	int res = 0;

	for(int i=0; i<tourns->size(); i++){
		for(int j=0; j<tourns->at(i)->size(); j++){
			if(tourns->at(i)->at(j) == x)
				res++;
		}
	}

	return res;
}

//Indices des tournées ou apparait x
vector<int> tourneesContains(regroupements tourns, int x)
{
	vector<int> res;

	for(int i=0; i<tourns->size(); i++){
		for(int j=0; j<tourns->at(i)->size(); j++){
			if(tourns->at(i)->at(j) == x)
				res.push_back(i+1);
		}
	}

	return res;
}


int main(int argc, char *argv[])
{	
    if (argc < 2)
    {
        cout << "Veuillez spécifier un fichier en argument" << endl;
        return 1;
    }
    
	/* Déclarations des variables (à compléter) */

	donnees p; 
	double temps;
		
	/* Chargement des données à partir d'un fichier */
	
	lecture_data(argv[1],&p);
	
	/* Lancement de la résolution... */

	crono_start(); // .. et donc du chronomètre

	/* .... */
    
    //==================================
    //Prélude  --  Déclarations
    //==================================

    int n = p.nblieux - 1; //n
    int Ca = p.capacite; //Ca
    int* v = p.demande; //d1,d2,d3,...,dn
    
    int** cv = p.C; //matrice c
    int cc = p.nblieux;


    //==================================
    //Part 1  --  Regroupements
    //==================================

    //Liste des regroupements
    regroupements list = regroupements_create(n, Ca, v);
    
    //Liste des couts de chaque regroupement
    vector<int> coutsTotaux = vector<int>();
    coutsTotaux.reserve(list->size());

    //A décommenter pour afficher les regroupements (sans leur coût)

    /*for (int i = 0; i < list->size(); i++){
    	cout << i << " : ";
    	for(int j = 0; j < list->at(i)->size(); j++){
    		cout << list->at(i)->at(j) << " ";
    	}
    	cout << endl;
    }*/


    //==================================
    //Part 2  -- Voyageur de Commerce
    //==================================
    
    for (int i = 0; i < list->size(); i++)
    {
        vector<int>* regroupement = list->at(i);
        
        int coutM = regroupement_get_cout_minimum(regroupement, cv, cc);
        coutsTotaux.push_back(coutM);
                        
        //A décommenter pour afficher les regroupements (avec leur coût)
        
        /*cout << (i+1) << " : ";
        regroupement_print(regroupement);
        cout << " : " << coutM << endl;*/
    }

    
    
    //==================================
    //Part 3  -- Partitionnement
    //==================================

    glp_prob *prob = glp_create_prob();
    int nbContraintes = p.nblieux -1; //Nombre de contraintes du probleme
    int nbVariables = list->size(); //Nombre de variables du problème

	glp_set_prob_name(prob, "ProblemeGLPK"); //On nomme le problème : ProblemeGLPK (comme ça c'est clair)
	glp_set_obj_dir(prob, GLP_MIN);  //Objectif Minimisation

	//Une ligne par puit

	glp_add_rows(prob, n);

	//Les n puits sont actifs

	for(int i=1; i<=n; i++){
		glp_set_row_bnds(prob, i, GLP_FX, 1.0, 1.0);
	}

	//Une ligne par regroupement possible
	glp_add_cols(prob, nbVariables);

	//Obligation de faire des char** pour glpk pour stocker le nom de chaque variable
	char** nomVariable = (char**) malloc (nbVariables * sizeof(char *));
	

	for(int i=0; i<nbVariables; i++){
			nomVariable[i] = (char*) malloc (6 * sizeof(char));
			char* tmp = (char *) malloc (6  * sizeof(char)); //i sous la forme d'un tableau de char
			sprintf(tmp, "%d", i+1);
			strcpy(nomVariable[i],"X");
			strcat(nomVariable[i], tmp);
			glp_set_col_name(prob, i+1 , nomVariable[i]); //Chaques colonnes (trajet possible) est appelé Xi
			delete [] tmp;

			//Variables binaires
			glp_set_col_bnds(prob, i+1, GLP_DB, 0.0, 1.0); 
			glp_set_col_kind(prob, i+1, GLP_BV);
			
			//Associe le cout du trajet a chaques variables
			glp_set_obj_coef(prob, i+1, coutsTotaux.at(i));
	}

	//Création de la matrice
	//Pour chaques puits, on récupères le nombre de tournées qui le contiennent et on additionne ce nombre à elemMatCreuse pour connaitre le nombre de valeurs qu'il y aura pour l'allocation memoire
	int nbElemMatCreuse = 0;	

	for(int i=0; i<nbContraintes; i++){
		nbElemMatCreuse += nbApparitions(list, i+1);
	}

	//Creation des tableaux pour le glpk
	int* lignes = (int*) malloc ((1 + nbElemMatCreuse)*sizeof(int));
	int* colonnes = (int*) malloc ((1 + nbElemMatCreuse)*sizeof(int));
	double* valeurs = (double*) malloc ((1 + nbElemMatCreuse)*sizeof(double));

	//Pour chaques puits
	int compteurMatrice = 1; //GLPK part de 1
	vector<int> tournees;
	for(int i = 0; i < nbContraintes; i++){
		//On récupère toutes les tournées (regroupements) qui contiennent le puit
		tournees = tourneesContains(list, i+1);
		//Pour chaque tournée possible associée
		for(int j = 0; j < tournees.size(); j++){
			//On donne le puit en tant que ligne
			lignes[compteurMatrice] = i+1;
			//On indique la tournée en tant que colonne
			colonnes[compteurMatrice] = tournees[j];
			//Et on active cette valeur pour la matrice creuse 
			valeurs[compteurMatrice] = 1.0; 
			compteurMatrice++;
		}
	}

	glp_load_matrix(prob,nbElemMatCreuse,lignes,colonnes,valeurs); 

	//Création d'un fichier .lp qui contient le contenu du probleme (variables,objectif,etc..)
	glp_write_lp(prob,NULL,"problemeGLPK.lp");
	glp_simplex(prob,NULL);	
	glp_intopt(prob,NULL);

	//Récupération des résultats
	double* tabRes = (double *) malloc (nbVariables * sizeof(double)); //les groupes
	double resOpti = glp_mip_obj_val(prob); //Le resultat optimal

	for(int i = 0; i < nbVariables; i++){
		tabRes[i] = glp_mip_col_val(prob,i+1);	
	} 

	cout << "Resultat Optimal = " << resOpti << endl;
	cout << "Groupes Choisis : " << endl;
	for(int i = 0; i < nbVariables; i++){
		if((int)(tabRes[i] + 0.5) != 0){
			cout << "Groupe " << i << " = (";
			for(int j=0; j < list->at(i)->size(); j++){
				cout << " " << list->at(i)->at(j) << " ";
			};
			cout << ")" << endl;
		}
	}

	/* ... */

	/* Problème résolu, arrêt du chrono */
	
	crono_stop();
	temps = crono_ms()/1000,0;
	
	/* Affichage des résultats */
	
	cout << "Temps d'execution : " << temps << endl;
	
	/* libération mémoire */

    regroupements_free(list);
	free_data(&p);
	
	/* J'adore qu'un plan se déroule sans accroc! */
	return 0;
}
