//NYUNTING Elbert

// Exercice date

#include <iostream>

using namespace std;

//-------------------
//algo année bissectile

int bissectile (int y) { // fonction pour voir si l'annee est bissectile.

//variables 

	if ( y % 4 == 0 && y % 100 != 0 ) {
	
		
		return true;
	}
	else if (y % 400 == 0) {
		 
		return true;
	}
	else {

		return false;
	}
}


//--------------------------
//Debut
int main() {

//Variables
int j; // jour	
int m; //mois
int a; //année

//saisie
	cout << "Saisissez une date sous forme jour, puis mois, puis annee : " << endl;
	cin >> j >> m >> a;
 
	while (m > 12 || m < 1) {
	cout << "Saisissez une date sous forme jour, puis mois, puis annee : " << endl;
	cin >> j >> m >> a;
	}
//fin saisie

//--------------

//partie longue pour empecher l'utilisateur de faire le malin et saisir 30 jours pour fevrier, ou 31 jours pour novembre, etc
	if (bissectile (a)) { //annee bissectile
		if (m == 2) {
		while ( j > 29 || j < 1) {
		
		cout << "Saisissez une date sous forme jour, puis mois, puis annee : " << endl;
		cin >> j >> m >> a;
		}
		}
		else if (m == 4 || m == 6 || m == 9 || m == 11) {
		while ( j > 30 || j < 1) {
		cout << "Saisissez une date sous forme jour, puis mois, puis annee : " << endl;
		cin >> j >> m >> a;
		}
		}
		else {
		while ( j > 31 || j < 1) {
		cout << "Saisissez une date sous forme jour, puis mois, puis annee : " << endl;
		cin >> j >> m >> a;
		}
	
	}
	}
	else  {
		if (m == 2) { //annee non bissectile
		while ( j > 28 || j < 1) {
		
		cout << "Saisissez une date sous forme jour, puis mois, puis annee : " << endl;
		cin >> j >> m >> a;
		}
		}
		else if ( m == 4 || m == 6 || m == 9|| m == 11) {
		while ( j > 30 || j < 1) {
		cout << "Saisissez une date sous forme jour, puis mois, puis annee : " << endl;
		cin >> j >> m >> a;
		}
		}
		else {
		while ( j > 31 || j < 1) {
		cout << "Saisissez une date sous forme jour, puis mois, puis annee : " << endl;
		cin >> j >> m >> a;
		}
		
		}
		
}

//fin partie longue (peut etre une fonction?)

//partie affichage (peut etre une fonction?)
//affichage de la bissectilité (?) 
		if (bissectile (a)) {
			cout<< a << " est une annee bissectile!  <:D" << endl;
		}
		else {
			cout<< a << " n'est pas une annee bissectile!  :'(" << endl;
		}
//------------------------
//affichage date
		if (m == 2 && bissectile (a)){
		if (j == 29){
		cout << "1/3/"<< a << endl;
		cout << "ce mois a 29 jours" << endl;
		}
		else {
		cout << j+1 << "/" << m << "/" << a << endl;
		cout << "ce mois a 29 jours" << endl;
		}
	}
	else if (m == 2) {
		if (j == 28){
		cout << "1/3/"<< a << endl;
		cout << "ce mois a 28 jours" << endl;
		}
		else {
		cout << j+1 << "/" << m << "/" << a << endl;
		cout << "ce mois a 28 jours" << endl;
		} 
	}
	else if ( m == 12 ) {
		cout << "1/1/"<< a+1 << endl;
		cout << "ce mois a 31 jours" << endl;
		}
	else if ( m == 4 || m == 6 || m == 9|| m == 11) {
		if (j == 30){
		cout << "1/" << m+1 << a << endl;
		cout << "ce mois a 30 jours" << endl;
		}
		else {
		cout << j+1 << "/" << m << "/" << a << endl;
		cout << "ce mois a 30 jours" << endl;
		}
	} 
	else {
		if (j == 31){
		cout << "1/" << m+1 << a << endl;
		cout << "ce mois a 31 jours" << endl;
		}
		else {
		cout << j+1 << "/" << m << "/" << a << endl;
		cout << "ce mois a 31 jours" << endl;
		} 
	}
}

//FIN









