/* date.cpp - auteur : D. Boildieu et Y. Keraval
Role : dit si une date choisit par l'utilisateur est bissextile, donne le nombre de jours du mois et la date du lendemain.
*/

#include <iostream>

using namespace std;

//----------------------------------------------------

//fonction estbissextile (booleen determinant si l'annee est bissextile)


bool estbissextile (int annee) {
	bool estb;
	if (annee % 4 != 0) { //on verifie que l'annee est divisible par 4
		estb=false;
	}
	else{ 
		if (annee % 100 == 0) { //on verifie que l'annee est divisible par 100
			if(annee % 400 == 0) { //on verifie que l'annee est divisible par 400
			estb=true;
		}
		else {
			estb=false;
		}
	}
		else { 
			estb=true;
		}
	}
	return estb;
}

//----------------------------------------------------
//fonction principale


int main ()
{
	//declaration des variables
	int jours;
	int mois;
	int an;

	//entree de la date
	cout << ("Donnez un jours : ");
	cin >> jours;
	cout << ("Donnez un mois : ");
	cin >> mois;
	if ( mois < 01 || mois > 12 ) { // on verifie si le mois correspond au calendrier gregorien
		while ( mois < 01 || mois > 12 ) {
			cout << ("Donnez un mois : ");
			cin >> mois;
		}
	}
	cout << ("Donnez une annee : ");
	cin >> an;

	//calcul du nombre de jours et calcul du lendemain
	if ( (mois <= 07 && mois % 2 != 0) || (mois >= 8 && mois % 2 == 0) )  { // on verifie si c'est un mois ayant 31 jours
		if  ( jours < 01 || jours > 31 ) {	// on verifie que le jour est correcte
			while ( jours < 01 || jours > 31 ) {
				cout << ("Donnez un jours : ");
				cin >> jours;
			}
		}
		cout << "Ce mois comporte 31 jours." << endl;
		jours = jours+1;	
		if (jours == 32 ) { // on verifie si on doit changer de mois
				jours = 01;
			jours = 01;
			mois = mois +1;
			if (mois == 13) { // on verifie le passage de l'annee
				mois = 01;
				an = an+1;
			}
		}
	}
	else {
		if (mois != 02) { // on verifie si c'est un mois ayant 30 jours
			if  ( jours < 01 || jours > 30 ) { // on verifie que le jour est correcte
				while ( jours < 01 || jours > 30 ) {
					cout << ("Donnez un jours : ");
					cin >> jours;
				}
			}
			cout << "Ce mois comporte 30 jours." << endl;
			jours = jours+1;	
			if (jours == 31 ) { // on verifie si on doit changer de mois
				jours = 01;
				mois = mois +1;
				if (mois == 13) { // on verifie le passage de l'annee
					mois = 01;
					an = an+1;
				}
			}
		}
		else {
			if (estbissextile(an)==true) { // on verifie le nombre de jours du mois de fevrier
				if  ( jours < 01 || jours > 29 ) { // on verifie que le jour est correcte
					while ( jours < 01 || jours > 29 ) {
						cout << ("Donnez un jours : ");
						cin >> jours;
					}
				}
				cout << "Ce mois comporte 29 jours." << endl;
				jours = jours+1;	
				if (jours == 30 ) { // on verifie si on doit changer de mois
				jours = 01;
					jours = 01;
					mois = mois +1;
					if (mois == 13) { // on verifie le passage de l'annee
						mois = 01;
						an = an+1;
					}
				}
			}
			else {
				if  ( jours < 01 || jours > 28 ) { // on verifie que le jour est correcte
					while ( jours < 01 || jours > 28 ) {
						cout << ("Donnez un jours : ");
						cin >> jours;
					}
				}
				cout << "Ce mois comporte 28 jours." << endl;
				jours = jours+1;	
				if (jours == 29 ) { // on verifie si on doit changer de mois
				jours = 01;
					jours = 01;
					mois = mois +1;
						if (mois == 13) { // on verifie le passage de l'annee
						mois = 01;
						an = an+1;
						}
					}
				}
			}
		}
	
	// utilisation estbissextile et affichage
	if (estbissextile(an)==true) { 
		cout << "Cette annee est bissextile." << endl;
		}
	else {
		cout << "Cette annee n'est pas bissextile" << endl;
	}
	cout << "Demain sera le " << jours << "/" << mois << "/" << an << " :)" << endl;
	return (0);
}
