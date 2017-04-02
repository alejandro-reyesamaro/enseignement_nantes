/* 243_HUNAULT+MOHAMED_TP3-EX6.cpp
e136688z HUNAULT Marion
e146929F MOHAMED Aymana
Rôle : affiche un décalage circulaire
*/

#include <iostream>

using namespace std;

const int N = 4;

typedef struct {
	int contenu[N];
	int nb;
} T_tabEnt;

//----------------------------------------------------------
//procédure
//rôle : décale de decal les cases du tableau
void decalage(int decal, T_tabEnt & tab) {
	T_tabEnt tempo;
	for (int i=0; i<tab.nb; i++) {
		tempo.contenu[i] = tab.contenu[i];
	}
	for (int i=0; i<tab.nb; i++) {
		tempo.contenu[i] = tab.contenu[(i+decal)%(tab.nb)];
		cout << tempo.contenu[i] << " | ";
	}
}

//----------------------------------------------------------
//procédure
void decal1(T_tabEnt & tab) {
	int stock = tab.contenu[tab.nb - 1];
	for (int i=1; i<tab.nb; i++) {
		tab.contenu[i+1] = tab.contenu[i];
	}
	tab.contenu[0] = stock;
}

//----------------------------------------------------------
//procédure
void decalageRecursif(int decal, T_tabEnt & tab) {
	if (decal>=1) {
		decal1(tab);
		decalageRecursif(decal-1, tab);
	}
}

//----------------------------------------------------------
//fonction principale
int main() {
	T_tabEnt tab;
	int decal;
	int i = 0;
	tab.nb = N;
	cout << "remplir le tableau à " << N << " cases " << endl;
	while (i<N) {
		cout << "case n° " << i+1 << "\n";
		cin >> tab.contenu[i];
		i++;
	}
	cout << "decaler de combien de cases ? ";
	cin >> decal;
	decalage(decal, tab);
	cout << endl;
	decalageRecursif(decal, tab);
	return(0);
}

/* Jeu d'essai :
tableau {4,8,5,3} decalage 2
affiche : 5 | 3 | 4 | 8 | pour la procédure itérative

tableau {6,8,1,2} decalage 4
affiche : 6 | 8 | 1 | 2 | pour la procédure itérative

la procédure récursive n'affiche rien, pas eu le temps
*/
