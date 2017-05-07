/* 56.cpp - auteur : Boudeville-Raimbaut Orlane, Raffin Valentin groupe 243.
 * TP 5 Exercice 5.7
*/


#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

//type vecteurs
struct T_vect {
	int taille;
	int *ptab;
};


int taille_vect ( T_vect vect )
{
	return (vect.taille);
}

T_vect saisie () 
{
	int i , nb;
	T_vect vect;
	int val;
	
	cout << "Saisir la taille du vecteur ";
	cin >> nb;
	vect.taille = nb;
	vect.ptab = new int [nb];
	for (i=0 ; i<=nb-1 ; i++)
	{
		cout << "saisir la valeur " << i ; 
		cin >> val;
		vect.ptab[i] = val;
	}
	return (vect);
}

int produit_sc ( T_vect va , T_vect vb)
{
	int i;
	int res = 0;
	if (taille_vect (va) == taille_vect (vb) && taille_vect (va)!= 0)
	{
		for (i=0 ; i<=va.taille-1 ; i++)
		{
			res = res + va.ptab[i] * vb.ptab[i];
		}
	return (res);
	}
	else
	{
		cout << "le produit scalaire ne peut pas etre calculer ";
		return(res);
	}
}	
/*int main () //exemple avec 2 vecteurs saisie
{
	T_vect va , vb;
	
	va.taille = 2;
	vb.taille = 2;
	va.ptab = new int[2];
	vb.ptab = new int[2];
	va.ptab[0] = 3;
	va.ptab[1] = 2;
	vb.ptab[0] = 1;
	vb.ptab[1] = 3;
	cout << produit_sc (va,vb) << endl;
} 
*/
int main ()
{
	fstream flux;
	T_vect va , vb ;
	
flux.open(vecteur.c_str(), ios::in);   // ouverture du fichier en lecture
	if (flux) 
    {
    flux >> val;
		while (!(flux.eof())) 
		{
			for (i=0 ; i<=va.taille ; i++)
			{
				flux >> val;
				va.ptab[i] = val;
			}
		flux.close();
		}
    }
  else 
    {
    cout << "\nImpossible d'ouvrir le fichier " << nom << "\n";
	}
    vb = saisie ();
    cout << produit_sc (va , vb) ;
}
