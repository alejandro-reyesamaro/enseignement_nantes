#ifndef GESTION_DONNEES
#define GESTION_DONNEES

/*

Projet RO 2017
Chedotal Corentin & Duclos Romain - 601A

Fichier gestion_donnees.hpp :

Contient toutes nos structure de données ainsi que les méthodes pour :
- lecture des données depuis un fichier.
- calcul des regroupements
- calcul des distances
- mise à jour des données du problème

*/
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>  //pour le type vector
#include <fstream> //pour la lecture depuis un fichier
//#include <glpk.h>
//#include "tsp_brute_force.hpp"

using namespace std;


//Structure de données pour la gestion des sous problèmes tsp
struct donnees_li
{
    int nbsomm;
    int nbcontr;
    int nbvar;
    int nbcreux;
    vector<int> c;
};

//Structure contenant les donnees du problème
struct donnees_p
{
	int nbvar; //n
    int nbcontr; //m
    vector<int> couts; //Tableau des coefficients de chaque variable dans la fonction objectif
    vector< vector<int> > contr; //Tableau de tableaux indiquant les indices des variables dans chaque contrainte
    vector<int> sizeContr; //Tableau contenant le nombre de variables dans chaque contrainte
};

//Structure de données pour avoir chaque point de pompage avec son indice et la quantité d'eau disponible
struct pt_pomp
{
    int ind;
    int quant;
};

//Structure pour regrouper les informations d'un regroupement
struct regroupement
{
    int indice;
    vector<pt_pomp> regr;
    int l;
};

//Structure pour gérer les données sorties du fichier
struct donnees_f
{
    int nblieux; /* Nombre de lieux (incluant le dépôt) */
    int capacite; /* Capacité du véhicule de livraison */
    vector<int> demande; /* Demande de chaque lieu (la case 0 est inutilisée car le dépôt n'a aucune demande à voir satisfaire) */
    vector< vector<int> >C; /* distancier (les lignes et colonnes 0 correspondent au dépôt) */
};

//Structure de données pour le calcul par force brute des distances de chaque regroupement
struct donnees_bf
{
    regroupement rg;   //Un regroupement à tester
    vector<int> distancier; //Le distancier associé à ce regroupement
};

/*
Structure de données pour le drone, en fait pour le moment c'est juste un entier mais ptete
qu'il faudra rajouter des choses plus tard et puis ca mesert à représenter 
les drones dans mon code
*/
struct drone
{
    int capa;
};

//Structure pour stocker l'ensemble des regroupements, il y a un seul attribut à l'intérieur mais c'était plus simple pour s'y retrouver
struct liste_regr
{
    std::vector<regroupement> ens_regr;
};

//Structure ens_pompes, contient juste un tableau de pompes mais c'était plus pratique pour l'utiliser dans nos méthodes
struct ens_pompes
{
    vector<pt_pomp> v;
};

//Méthode pour la lecture des donnees
void lecture_data(string file, donnees_f & f)
{
	int i,j,val;

	vector<int> temp;


	ifstream fichier;
	fichier.open(file.c_str());  // on ouvre le fichier en lecture
 	
    if(fichier)  //si l'ouverture a réussi
    {   
    	//Lecture du nombre de lieux
    	fichier >> val;
    	f.nblieux = val;

    	//Lecture de la capacite
    	fichier >> val;
    	f.capacite = val;

    	//Lecture des demandes des clients
    	for (i = 0; i < f.nblieux - 1; ++i)
    	{
    		fichier >> val;
    		f.demande.push_back(val);
    	}

    	//Lecture du distancier
    	for (i = 0; i < f.nblieux; ++i)
    	{
    		for (j = 0; j < f.nblieux; ++j)
    		{
    			fichier >> val;
    			temp.push_back(val);
    		}

    		f.C.push_back(temp);
    		temp.clear();
    	}

    	fichier.close();  //fermeture du fichier
    }
    else  //sinon
    	cerr << "Impossible d'ouvrir le fichier" << endl;

} //Fin de lecture_data

//Structure de données pour le calcul par force brute des distances de chaque regroupement
struct donnees_bf;

int tsp_brute_force(donnees_bf b)
{
    //Variables de boucle
    int i;

    //Pour garder en mémoire les indices des arcs parcourus
    int ind;

    //Check pour vérifier qu'on passe bien par chaque sommet
    int check_somm = 0;

    //Minimum d'un ensemble d'arc
    int min;

    //Longueur du chemin
    int longueur = 0;

    //Création de flags_arc pour vérifier qu'on est pas passé par une arrête
    int flags_arc[b.distancier.size()];

    for(i=0; i<b.distancier.size(); ++i)
    {
        flags_arc[i] = 0;
    }

    //Création de flags_som our vérifier qu'on passe max 2 fois par sommet
    int flags_somm[b.rg.regr.size()];
    for(i=0; i<b.distancier.size(); ++i)
    {
        flags_arc[i] = 0;
    }

    //On commence à parcourir les chemins
    //On pars de la base et on prend le plus petit qui pars de la base
    min = b.distancier[0];

    for (i = 0; i < b.distancier.size(); ++i)
    {
        if(b.distancier[i]<=min)
        {
            min=b.distancier[i];
            ind = i;
        }
    }

    longueur = longueur + min;

    flags_arc[ind] = 1;

    //Ensuite on check tous les chemins
    //Tant qu'on est pas passé par tous les sommets plus la base (+1)
    i = 0;
    min = b.distancier[0];

    while(check_somm != b.rg.regr.size() + 1)
    {
        if(b.distancier[i]<=min)
        {
            min=b.distancier[i];
            ind = i;
            if(flags_arc[ind]==0 && flags_somm[ind]<2)
            {
                check_somm++;
                flags_arc[ind] = 1;
                flags_somm[ind] = flags_somm[ind]++;
                longueur = longueur + min;

            }
        }

        i++;
    }

    return longueur;

} //Fin tsp_brute_force


/*
Procédure genere_contr
Permet de calculer les indices de chaque variable dans les contraintes
ainsi que le nombre de variables dans chacune de ces contraintes
*/
void genere_contr(donnees_p & p, liste_regr reg)
{   
    //Variables de boucle
    int i;
    int j;
    int k;

    //Indice du point de pompage que l'on check
    int ind = 1;

    //Vecteur contenant les indices des regroupements
    vector<int> temp;

    //Pour chaque contrainte (donc chaque point de pompage)
    for (k = 0; k < p.nbcontr; ++k)
    {
        //On parcours l'ensemble des regroupements
        for (i = 0; i < reg.ens_regr.size(); ++i)
         {
            //Ensuite pour chaque regroupement de point de pompage
            for (j = 0; j < reg.ens_regr[i].regr.size(); ++j)
            {
                //Si l'indice (k) de la pompe est dans le regroupement j
                if(ind == reg.ens_regr[i].regr[j].ind)
                {   
                    //Alors ce regroupement d'indice i est dans la contrainte de k
                    temp.push_back(i+1);
                }
            }
        }

        //On ajoute à la contrainte k l'ensemble des indices des regroupements
        p.contr.push_back(temp);

        //On met à jour le nombre de variables dans cette contrainte
        p.sizeContr.push_back(temp.size());

        //On vide le vecteur contenant les indices avant de recommencer
        temp.clear();

        ind++;

    }//Fin du parcours des contraintes


} //Fin de genere_contr

/*
Cette méthode renvoie la somme des quantités d'un tableau de pt_pomp
Ca me sert à savoir si une tournée demande trop de capacité au drone
*/
int somme_capa(vector<pt_pomp> v)
{
    int somme = 0;

    for (int i = 0; i < v.size(); ++i)
    {
        somme += v[i].quant;
    }

    return somme;
}

/*
Méthode pour obtenir les parties d'un ensemble
à partir du drone et des points de pompage
*/
void genere_regroupement(liste_regr & lreg, ens_pompes e_ppes, drone d)
{
    
    //Indices de boucles
    int i = 0;
    int j;
    int imax = pow(2,e_ppes.v.size())-1; //la c'est le nombre de permutations possibles (2^n -1)
    int jmax = e_ppes.v.size() - 1;

    int ind = 1;  //Indice des regroupements

    //Un regroupement
    regroupement s;


    //Tant qu'on a pas "touché" toutes les permutations
    while (i <= imax)
    {
        
        j = 0;

        //Pour toutes les pompes
        while (j <= jmax)
        {
            //On décale les bits des indices de j et on regarde si il ya un 1
            //En fait on trouve les permutations avec l'écriture binaire des indices de j
            if((i>>j)&1 == 1)
            {   
                //Et la on met dans une tournée une des pompes
                s.regr.push_back(e_ppes.v[j]);
            }

            j++;
        }

        //Ici je test qu'une tournée ne demande pas plus que la capacité du drone
        //(et dans ce cas là je ne la prend pas)
        if (somme_capa(s.regr) <= d.capa && s.regr.size() !=0 )
        {  
            //On ajoute s à la liste des regroupements
            s.indice = ind;
            lreg.ens_regr.push_back(s);
            ind++;

        }
        
        i++;
        s.regr.clear();
    
    }//Fin du while

} //Fin de genere_regroupement


/*
Méthode très simple pour remplir le tableau contenant l'ensemble des pompes avec leur indices, quantité,...
*/

void genere_ens_pompes(ens_pompes & e_ppes, donnees_f f)
{
    //Variable pour les points de pompages
    pt_pomp pt;

    //On parcours le nombre de lieux (sans la base)
    for (int i = 0; i < f.nblieux - 1; ++i)
    {
        pt.ind = i + 1 ; //je commence les indices à 1, par sécurité je laisse le 0 à la base
        pt.quant = f.demande[i]; //On a dans f la quantité d'eau de chaque point
        e_ppes.v.push_back(pt);
    }

}//Fin de genere_ens_pompes


//Méthode est_present renvoie vraie si un élément x passé en paramètre
//est dans un tableau t de pt de pompage passé aussi en paramètre
bool est_present(int x, vector<pt_pomp> t)
{
    int i = 0;
    while (i<t.size())
    {
        if (x==t[i].ind || x==0) return true;
        ++i;
    }
}

//Méthode pour récupérer les données qu'on envoie au calcul brute force
void genere_brute_force(donnees_bf & b, donnees_f f, regroupement r)
{
    b.rg = r;
    for (int i = 0; i < f.C.size(); ++i)
    {
        for (int j = 0; j < f.C.size(); ++j)
        {
            if(est_present(i,r.regr) && est_present(j,r.regr) && i!=j)
            {
                b.distancier.push_back(f.C[i][j]);
            }
        }
    }

}//Fin de genere_brute_force

//Méthode genere_couts pour avoir dans chaque regroupement la distance min de parcours
// calculée avec brute force
void genere_couts(donnees_p p,donnees_f f,liste_regr r)
{
    //Structure de données à mettre dans le brute force
    donnees_bf b;
    int z; //La valeur que l'on récupère
    for (int i = 0; i < r.ens_regr.size(); ++i)
    {   
        //Pour chaque regroupement les données qu'il faut
        genere_brute_force(b,f,r.ens_regr[i]);

        //Ensuite on rècupère la valeur voulue
        z = tsp_brute_force(b);

        //Et on l'ajoute aux données de glpk
        p.couts.push_back(z);

    }
}//Fin de genere_couts

/*
Procédure remplis_donnees
Permet d'affecter toutes les données dans la structure donnees_p pour
ensuite les envoyer au problème écrit avec glpk
*/
void remplis_donnees(donnees_p & p, donnees_f f)
{
    //Structure de données intermédiaires avant de passer à aux données envoyées à glpk
    ens_pompes ep;
    liste_regr er;
    drone d;

    //On fait l'ensemble des pompes, regroupements, etc..
    genere_ens_pompes(ep,f);
    d.capa = f.capacite;
    genere_regroupement(er,ep,d);

    //Données pour glpk
    p.nbvar = er.ens_regr.size(); //En fait le nombre de variables c'est le nombre de regroupements
    p.nbcontr = f.nblieux - 1; //Le nombre de variables c'est le nombre de lieux mais sans la base
    genere_couts(p, f,er ); //On utilise la méthode genere_couts qui permet de calculer le chemin min de chaque regroupement, ce sont donc les coef de la fonction objectif
    genere_contr(p, er); //A partir du tableau des regroupements on détermine les indices des variables dans les contraintes
                          //On remplit en même temps le nombre de variables dans chaque contrainte
} //Fin de remplis_donnees



//Méthode pour passer de nos structures de donnes pour BladeFlyer
//aux donnees dont on a besoin pour le sous problème tsp.
void genere_sous_tsp(donnees_li & l, donnees_f f, regroupement r)
{
    l.nbsomm = r.regr.size() + 1;
    l.nbvar = l.nbsomm * l.nbsomm - l.nbsomm;
    l.nbcontr = l.nbsomm + l.nbsomm + l.nbvar;
    l.nbcreux = l.nbsomm * l.nbsomm + l.nbsomm * l.nbsomm ;

    int pos = 0;
    for (int i = 0; i < f.C.size(); ++i)
    {
        for (int j = 0; j < f.C.size(); ++j)
        {
            if(est_present(i,r.regr) && est_present(j,r.regr) && i!=j)
            {
                l.c.push_back(f.C[i][j]);
                pos++;
            }
        }
    }
} //Fin de genere_sous_tsp





#endif