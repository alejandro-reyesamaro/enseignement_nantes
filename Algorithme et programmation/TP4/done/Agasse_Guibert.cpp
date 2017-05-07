// groupe 243
// AGASSE Laure E153993J GUIBERT Justine E162787S
//TDTP5 exercice 5.7 vecteurs
//Rôle : calcul d'un produit scalaire entre un vecteur saisi par l'utilisateur et une série de données contenu dans un fichier.

#include<iostream>
#include<string>
#include<math.h>
#include <fstream>
#include <stdlib.h>     /* atoi */

using namespace std;

//-----------------enregistrement du vecteur ----------------
struct T_vecteur {

	int taille;
	float *ptab;
};

//-----------------fonction saisie vecteur ----------------
T_vecteur saisie_vecteur(){
	int nb;
	int i;
	float val;
	T_vecteur vect;

	cout << " Saisir nb" << endl;
	cin >> nb ;
	vect.taille = nb;
	vect.ptab = new float[nb];

	for (i = 0; i < nb; i++){
	
		cout << "saisir val" << endl;
		cin >> val;
		vect.ptab[i] = val;
	}
	return (vect);
}

//-----------------fonction produit scalaire ----------------
int produit_scalaire(T_vecteur v1, T_vecteur v2)
{
	int i;
	float acc;
	if (v1.taille == v2.taille){
		acc=0;
		for (i=0; i<=v1.taille-1;i++){
			acc = acc+v1.ptab[i]*v2.ptab[i];
		}
	return acc;
	}
	else{
		return 0;
	}	
}

//-----------------algorithme principal ----------------

int main()
{
	T_vecteur v3;
	fstream fichier;
	v3 = saisie_vecteur();
	string val_str;
	T_vecteur vect_fich;
	int val;
	vect_fich.ptab= new float[v3.taille];
	vect_fich.taille=v3.taille;
	fichier.open("fichier_vecteur.txt",ios::in);
	if (fichier){
		int i = 0;
		while (!(fichier.eof())) 
		      {		      	
			fichier >> val_str;
			val = atoi (val_str.c_str());
			vect_fich.ptab[i] = val;
			i=i+1;
		      }	
	}else{
		cout << "Ouverture impossible du fichier"<< endl;
	}
	cout << produit_scalaire (v3, vect_fich)<< endl;
	fichier.close();
	return 0;
}

/*Conclusion: Notre algorithme fonctionne
	input: "5" et "6"
		dans le fichier: "4" et "5"
	output: 50
/*
