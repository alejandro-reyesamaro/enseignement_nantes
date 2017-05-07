/* produitscalaire.cpp groupe 243 Célia BOURHIS et Lisa ORIZET TD5/TP5 Exercice 5.7-8/9
rôle : fonction qui prend deux vecteurs en paramètres et retourne leur produit scalaire 
s'il peut être calculé. 
rôle : algorithme qui calcule le produit scalaire entre un vecteur saisi par l'utilisateur 
et une série de données contenues dans un fichier
*/

#include<iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std ;

// Déclaration du vecteur
struct t_vecteur {
int taille;
double * ptab;
};


//Fonction

double produitscal(t_vecteur vect1, t_vecteur vect2)
{
	double somme;
	int i;
	double produit;

//Initialisation
	somme=0;

	if ((vect1.taille != vect2.taille)||(vect1.taille == 0)||(vect2.taille == 0)) {
		return (0);
	} else {
		for (i=0; i<vect1.taille;i++) {
			produit=vect1.ptab[i]*vect2.ptab[i];
			somme=somme + produit;
		}
	return (somme);
	}
}
	
//Fonction

 t_vecteur saisievect()
{
	int nb;
	int i;
	double val;
	t_vecteur vect;


//Initialisation
	cout << "taille ?";
	cin >> nb;

	vect.taille = nb;
	vect.ptab = new double[vect.taille];
	
	for (i=0; i<nb;i++) {
		cout << "réel ?";
		cin >> val;
		vect.ptab[i] = val;
	}

	return (vect);
}

//-----------------------------------------------------------------------------------------



//Algorithme

int main()
{
	t_vecteur vectutilis;
	string nom;
	fstream fic;  // flux_fichier
	double num;
	t_vecteur stock;
	int i;
	int nb;

	vectutilis=saisievect();

	nb=0;
	cout << "Veuillez saisir le nom d'un fichier ";
	cin >> nom;

	fic.open(nom.c_str(), ios::in); //ouverture du fichier en lecture
	if (fic) {
		fic >> num;
		 while (!(fic.eof())) {
    			nb=nb+1;
			fic >> num;
      		}
		fic.close(); //fermeture du fichier ouvert en lecture
		stock.taille=nb;
		stock.ptab=new double[nb];
		fic.open(nom.c_str(), ios::in); //ouverture du fichier en lecture
		i=0;
		fic >> num;
		while (!(fic.eof())) {
			stock.ptab[i]=num;
			i++;
			fic >> num;
      		}
		fic.close(); //fermeture du fichier ouvert en lecture
	}
	cout << produitscal(vectutilis, stock);
	delete[] stock.ptab;
	delete[] vectutilis.ptab;
}

/*Jeu d'ssai : 
- cas 1 : cas où le produit scalaire est calculé
fichier essai.txt "1.2
		   2
		   34"
vecteur saisi ar l'utilisateur : "26
				  1.2
				  3"
on obtient 155.44
- cas 2 : deux vecteurs de taille différentes
- cas 3 : la taille d'un des vecteurs est nulle

*/












