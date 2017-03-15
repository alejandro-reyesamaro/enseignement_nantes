/*Raimbault Charlotte Jouaud Flora
Décalage circullaire */

#include <iostream>

using namespace std;

const int N = 10;

//--------------------------------------
//enregistrement type tableau de N entiers et le nombre d'entiers contenus
typedef struct {
	int contenu[N];
	int nb;
} T_TabEnt;

//--------------------------------------
//procédure décalant de manière circulaire les cases d'un tableau, de manière itérative
void decalage (int decal , T_TabEnt & tab) {
	T_TabEnt tempo;
	int indice;
	
	//recopie du tableau
	for (indice = 0; indice < tab.nb; indice++) {
		tempo.contenu[indice] = tab.contenu[indice];
	}

	//restitution avec décalage
	for (indice = 0; indice < tab.nb; indice++) {
		tab.contenu[(indice+decal) % tab.nb] = tempo.contenu[indice];
	}

}

//-------------------------------------
//procédure décalant de manière circulaire les cases d'un tableau, de manière récursive
void decal (T_TabEnt & table) {
	int stock;
	stock = table.contenu[table.nb-1];
	int delta;

	//décalage du tableau
	for (delta = 1; delta < table.nb; delta++) {
		table.contenu[table.nb-delta] = table.contenu[table.nb-delta-1];
	}

	table.contenu[0] = stock;

}

//--------------------------------------
//procédure affichant les éléments contenus dans le tableau
//utilisée dans notre algorithme de test
void affiche_tableau (T_TabEnt table ) {
	int ind;
	for (ind = 0; ind < table.nb; ind++){
		cout << table.contenu[ind]<<endl;
	}
}

//---------------------------------------------
//procédure permettant à l'utilisateur de saisir les valeurs du tableau
//utilisée dans notre algorithme de test
void saisie_tableau (T_TabEnt & table) {
	int ind;
	cout << "Combien de cases voulez-vous à votre tableau ?";
	cin >> table.nb;
	for (ind = 0; ind < table.nb; ind++) {
		cout << "Saisissez la valeur de la case " << ind;		
		cin >> table.contenu[ind];
	}
}



//--------------------------------------
//algorithme principal de test
int main () {
	T_TabEnt tablo;
	int nbdecalage;

	//remplissage du tableau et affichage
	saisie_tableau (tablo);
	affiche_tableau (tablo);

	//décalage du tableau
	cout << "De combien de cases voulez-vous décaler le tableau ?";
	cin >> nbdecalage;

	//appel de la procédure itérative et affichage
	decalage (nbdecalage, tablo);
	cout << "decalage de " << nbdecalage << " cases vers la droite de manière itérative par rapport au tableau saisi." << endl;
	affiche_tableau (tablo);

	//appel de la procédure récursive et affichage
	decal (tablo);
	cout << "decalage de 1 case vers la droite de manière récursive par rapport au tableau décalé de manière itérative." << endl;
	affiche_tableau (tablo);

}
	
/*comme la constante de départ est égale à 10, il ne faut pas faire des tableau de plus de 10 cases*/

/*jeux d'essais:

premier jeu d'essai:

tableau saisi de 5 cases
1 2 3 4 5

De combien de cases voulez-vous décaler le tableau ?3
decalage de 3 cases vers la droite de manière itérative par rapport au tableau saisi.
3 4 5 1 2 

decalage de 1 case vers la droite de manière récursive par rapport au tableau décalé de manière itérative.
2 3 4 5 1


deuxième jeu d'essai:

tableau saisi de 1 case
5

De combien de cases voulez-vous décaler le tableau ?5
decalage de 5 cases vers la droite de manière itérative par rapport au tableau saisi.
5

decalage de 1 case vers la droite de manière récursive par rapport au tableau décalé de manière itérative.
5


troisième jeu d'essai:

tableau saisi de 4 cases
1 2 3 4

De combien de cases voulez-vous décaler le tableau ?0
decalage de 0 cases vers la droite de manière itérative par rapport au tableau saisi.
1 2 3 4

decalage de 1 case vers la droite de manière récursive par rapport au tableau décalé de manière itérative.
4 1 2 3

quatrième jeu d'essai :

tableau saisi de 6 cases
1 2 2 3 4 5

De combien de cases voulez-vous décaler le tableau ?3
decalage de 3 cases vers la droite de manière itérative par rapport au tableau saisi.
3 4 5 1 2 2

decalage de 1 case vers la droite de manière récursive par rapport au tableau décalé de manière itérative.
2 3 4 5 1 2

*/
	
