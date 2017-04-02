/* 243_HUNAULT_MOHAMED_TP1.cpp
e136688z HUNAULT Marion
e146929F MOHAMED Aymana
Rôle : dit si une année est bissextile ou non, donne le nombre de jour du mois
*/

#include <iostream>
using namespace std;

//-----------------------------------------------------
//structure de la date
struct T_DATE {
	int jour;
	int mois;
	int annee;
};

//------------------------------------------------------
//fonction retourne vrai si année donnée est bissextile
bool bissextile (T_DATE date, bool & booleen) {
	if (((date.annee%4 == 0)  && (date.annee%100 != 0)) || (date.annee%400 == 0)) {
		booleen = true;
	}
	return (booleen);
}

//-------------------------------------------------------
//procédure qui permet la saisie d'une date
void saisieDate(T_DATE & date) {
	cout << "entrer le jour : ";
	cin >> date.jour;
	cout << "entrer le numéro du mois : ";
	cin >> date.mois;
	cout << "entrer l'année : ";
	cin >> date.annee;
}

//--------------------------------------------------------
//fonction qui donne le nombre de jour d'un mois
int nombreJour(T_DATE date, bool booleen) {
	int nbJour = 0;
	if ((date.mois == 4) || (date.mois == 6) || (date.mois == 9) || (date.mois == 11)) {
		nbJour = 30;
	} else if (date.mois == 2) {
		if (bissextile(date, booleen)) {
            nbJour = 28;         // Alejandro: ???
		} else {
			nbJour = 29;
		}
	} else {
		nbJour = 31;
	}
	return (nbJour);
}

//-------------------------------------------------------
//fonction principale
int main () {
	T_DATE date;
	bool booleen = false;
	saisieDate(date);
	if (bissextile(date, booleen)) {
		cout << date.annee << " est une annee bissextile" << endl;
	}
	cout << "le nombre de jour du mois est " << nombreJour(date, booleen) << endl;
}

/*
essais avec année = 2015, 1996
mois = 2, 7, 6
jour = 26, 6, 2

Nous n'avons pas eu le temps de traiter la question 3
les deux autres questions fonctionnent
*/
