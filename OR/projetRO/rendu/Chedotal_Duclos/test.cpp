/*

Projet RO 2017
Chedotal Corentin & Duclos Romain - 601A

Fichier test.cpp :

Fichier de test de nos structures de données et méthodes

*/

#include <iostream>
#include "gestion_donnees.hpp"
//#include <glpk.h>
//#include "tsp_li.hpp"
//#include "tsp_brute_force.hpp"

using namespace std;

int main(int argc, char *argv[])
{	
	//Variables de boucle
	int i,j,k;

	//Structures à tester
	donnees_f f;
	donnees_p p;
	ens_pompes e_ppes;
	liste_regr e_reg;
	drone d;
	donnees_li l;
	donnees_bf b;


	cout << "-----------TEST LECTURE DEPUIS UN FICHIER-----------------" << endl;
	lecture_data(argv[1],f);

	cout << "nblieux " << f.nblieux << endl;
	cout << "capacite " << f.capacite << endl;	

	cout << "demande ";
	for (i = 0; i < f.demande.size(); ++i)
	{
		cout << f.demande[i] << " ";
	}

	cout << endl;
	cout << "C " << endl;

	for (k = 0; k < f.C.size(); ++k)	
	{
		for (j = 0; j <  f.C[k].size(); ++j)
		{
			cout << f.C[k][j] << " ";
		}
		cout << endl;
	}


	cout << "-----------TEST GENERATION ENS_PPES--------------------" << endl;
	genere_ens_pompes(e_ppes, f);
	cout << "indice pt_pomp : " ;
	for (i = 0; i < e_ppes.v.size(); ++i)
	{
		cout << e_ppes.v[i].ind << " ";
	}
	cout << endl;
	cout << "quantité eau : ";
	for (i = 0; i < e_ppes.v.size(); ++i)
	{
		 cout << e_ppes.v[i].quant << " ";
	}
	cout << endl;

	cout <<"---------TEST GENERATION REGROUPEMENT--------------------" << endl;
	d.capa = f.capacite;
	genere_regroupement(e_reg, e_ppes, d);
	cout << "nb regreoupements : " << e_reg.ens_regr.size() << endl;
	for (i = 0; i < e_reg.ens_regr.size(); ++i)
	{
		cout << "{";
		for (j = 0; j < e_reg.ens_regr[i].regr.size(); ++j)
		{
			cout << e_reg.ens_regr[i].regr[j].ind;
		}
		cout << "}" << endl;
	}
	
	cout <<"---------TEST GENERATION DONNEES GLPK--------------------" << endl;
	remplis_donnees(p,f);
	cout << "nbvar " << p.nbvar << endl;
	cout << "nbcontr " << p.nbcontr << endl;
	cout << "contraintes : " << endl;
	for (i = 0; i < p.nbcontr; ++i)
	{
		cout << i + 1 << "[";
		for (j = 0; j < p.sizeContr[i]; ++j)
		{
			cout << p.contr[i][j] << " ";
		}
		cout << "]" << endl;
	}

	/*
	*
	* Complétement faux, il faut génerer tous les sous tours (chose qu'on a complétement oublié)
	* c'est exponentielle le nombre de contrainte à généner -> pas vraiment faisable
	* Solution : écrire le tout avec de la programmation dynamique (génération de coupe)
	* -> on a pas le temps de faire ceci. Assez compliqué (pour notre niveau) et on aura pas le
	* temps de le faire.
	*
	cout <<"--------TEST GENERATION SOUS_TSP-------------------" <<endl;
	int z;
	genere_sous_tsp(l,f,e_reg.ens_regr[6]);
	cout << "nbsomm " << l.nbsomm << endl;
	cout << "nbcontr " << l.nbcontr << endl;
	cout << "nbvar " << l.nbvar << endl;
	cout << "nbcreux " << l.nbcreux << endl;
	cout << "c " << endl;
	for (i = 0; i < l.nbvar; ++i)
	{
		cout << l.c[i] << " " ;
	}
	cout << endl;



	z = calcul_li(l);
	cout << "z " << z << endl;
	*/


	/*
	Test de notre algorithme de force brute pour le calcul des distances des regroupements
	Comme nous n'avons pas reussi à le terminer, les résutats sont incorrects
	*/
	cout <<"--------TEST BRUTE FORCE----------------------------" <<endl;
	int z;
	genere_brute_force(b,f,e_reg.ens_regr[8]);
	z = tsp_brute_force(b);
	cout << " z " << z << endl;




	return 0;
}
