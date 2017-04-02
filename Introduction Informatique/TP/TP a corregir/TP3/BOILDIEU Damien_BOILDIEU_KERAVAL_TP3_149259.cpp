/*  decalage.cpp -- Auteurs : Boildieu Damien et Keraval Yann
Role : Decale de n case le contenu d'un tableau d'entiers
*/

#include<iostream>
using namespace std;

const int N = 100;

// declaration du type tableau utilise

typedef struct { 
	int contenu[N];
	int nb;
	} T_tabEnt ;

//---------------------------------------------------------
// procedure iterative
void decal1 (int decal, T_tabEnt & table) {
	T_tabEnt tempo;
	if (decal >= 0) {
		for (int pos = 0; pos < table.nb; pos++) { // on recopie le contenu du tableau dans un tableau "pivot" 
			tempo.contenu[pos] = table.contenu[pos];
		}
		for (int indice = 0; indice < table.nb; indice++) { // on effectue le decalage
			table.contenu[(indice+decal) % table.nb] = tempo.contenu[indice];
		}
	} else {
		cout << "on ne decale pas avec un nombre negatif" << endl;
	}
}

//------------------------------------------------------------
// procedure recursive

void decal2 (int decalbis, T_tabEnt & tableau) {
	int stock;
	if (decalbis >= 1) { // on verifie qu'il y a bien un decalage a faire
		stock = tableau.contenu[tableau.nb-1]; // on stocke la derniere valeur du tableau pour ne pas la perdre
		for (int compteur = 1; compteur < tableau.nb; compteur++) { // on decale le contenu du tableau de 1
			tableau.contenu[tableau.nb-compteur] = tableau.contenu[tableau.nb-compteur-1];
		}
		tableau.contenu[0]=stock;
		decal2 (decalbis-1, tableau);
	} else if (decalbis < 0) {
		cout << "on ne decale pas avec un nombre negatif" << endl;
	}
}

//--------------------------------------------------------------
// procedure d'affichage de tableau

void affiche_tableau (T_tabEnt tab) {
	if (tab.nb >= 1){ // on verifie que le tableau n'est pas vide
		for (int i = 0; i < tab.nb; i++) { // on affiche le contenu du tableau
			if (i != (tab.nb-1)) {
				cout << tab.contenu[i] << ",";
			} else {
				cout << tab.contenu[i];
			}
		}
	cout << endl;
	} else {
		cout << "Votre tableau est \"vide\"." << endl;
	}
}

//---------------------------------------------------------------
// fonction principale et test

int main () {
	
	// declaration du tableau

	T_tabEnt tabl;
	
	// remplissage du tableau de test

	tabl.contenu[0] = 1;
	tabl.contenu[1] = 2;
	tabl.contenu[2] = 3;	
	tabl.contenu[3] = 4;
	tabl.contenu[4] = 5;
	tabl.nb = 5;

	// test du tableau avec les valeurs 0, 1, 3, 5, 8, -2

	cout << "nous allons decaler de 0 cases avec les 2 procedures, le tableau est cense afficher 1,2,3,4,5 puis 1,2,3,4,5" << endl;
	decal1(0, tabl);
	affiche_tableau(tabl);
	decal2(0, tabl);
	affiche_tableau(tabl);
	cout << "nous allons decaler de 1 cases avec les 2 procedures, le tableau est cense afficher 5,1,2,3,4 puis 4,5,1,2,3" << endl;
	decal1(1, tabl);
	affiche_tableau(tabl);
	decal2(1, tabl);
	affiche_tableau(tabl);
	cout << "nous allons decaler de 3 cases avec les 2 procedures, le tableau est cense afficher 1,2,3,4,5 puis 3,4,5,1,2" << endl;
	decal1(3, tabl);
	affiche_tableau(tabl);
	decal2(3, tabl);
	affiche_tableau(tabl);
	cout << "nous allons decaler de 5 cases avec les 2 procedures, le tableau est cense afficher 3,4,5,1,2 puis 3,4,5,1,2" << endl;
	decal1(5, tabl);
	affiche_tableau(tabl);
	decal2(5, tabl);
	affiche_tableau(tabl);
	cout << "nous allons decaler de 8 cases avec les 2 procedures, le tableau est cense afficher 5,1,2,3,4 puis 2,3,4,5,1" << endl;
	decal1(8, tabl);
	affiche_tableau(tabl);
	decal2(8, tabl);
	affiche_tableau(tabl);
	cout << "nous allons decaler de -2 cases avec les 2 procedures, les fonctions vont dire que l'on ne decale et pas le tableau est cense afficher 2,3,4,5,1 puis 2,3,4,5,1" << endl;
	decal1(-2, tabl);
	affiche_tableau(tabl);
	decal2(-2, tabl);
	affiche_tableau(tabl);
	return 0;
}
