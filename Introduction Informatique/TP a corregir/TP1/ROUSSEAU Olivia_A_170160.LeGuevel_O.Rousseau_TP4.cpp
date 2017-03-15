/* 243_Rousseau+LeGuevel_TP11/02.cpp -auteurs: O.Rousseau et A.Le Guevel
Role : Cet algorithme nous indique si l'année est bissextile, le nombre de jours du mois donné et la date du lendemain.
*/

#include <iostream>

using namespace std ;

int main () 
{
int annee ; // Saisies de l'utilisateur
int jour ;
int mois ;
int nb_jours ; // Pour l'affichage du nombre de jours dans un mois
int jours_annee ; // Détermine si une année est bissextile ou non 
int demain_jour ; // Variables pour ne pas modifier les valeurs saisies initiales
int demain_mois ;
int demain_annee ;

// Saisie des données
cout << "Saisir un jour. ";
cin >> jour ;
cout << "Saisir le nombre correspondant au mois. ";
cin >> mois ;
cout << "Saisir une annee. ";
cin >> annee ;
demain_jour = jour ; // Prend les valeurs saisies pour être ensuite modifiées
demain_mois = mois ;
demain_annee = annee ;

// Année bissextile ou non ?
if ((annee % 4 == 0) && (annee % 100 != 0)) {
	cout << "L'année "<< annee << " est bissextile." << endl ;
	jours_annee = 366 ;
} 
else {
	if (annee % 400 == 0) {
		cout << "L'année "<< annee << " est bissextile." << endl ;
		jours_annee = 366 ;
	}
	else {
		cout << "L'année "<< annee << " n'est pas bissextile." << endl ;
		jours_annee = 365 ;
	}
}

// Le nombre de jours d'un mois
/* On a différencié 3 cas : de janvier à juillet sans février, de aout à décembre et le mois de février. Cela permet d'obtenir le nombre de jours selon la parité du mois.
*/
if (mois > 7) {
	if (mois % 2 == 0) {
		nb_jours = 31 ;
	}
	else {
		nb_jours = 30 ;
	}
}
if ((mois < 8) && (mois != 2)) {
	if (mois % 2 == 0) {
		nb_jours = 30 ;
	}
	else {
		nb_jours = 31 ;
	}
}
if (mois == 2) {
	if (jours_annee == 366) {
		nb_jours = 29 ;
	}
	else {
		nb_jours = 28 ;
	}
}
cout << "Le mois que vous avez choisi possède " << nb_jours << " jours." << endl ;

// La date du lendemain
/* On a différencié comme précédemment pour les mois. Nous avons ensuite ajouté une condition, si il s'agissait du dernier jour du mois.
*/
if (mois > 7) {
	if (mois % 2 == 0) {
		if (jour != 31) {
			demain_jour = demain_jour + 1 ;
		}
		else {
			demain_jour = 1 ;
			if (mois == 12) {
				demain_mois = 1 ;
				demain_annee = demain_annee + 1 ;
			}
			else {
				demain_mois = demain_mois + 1 ;
			}
		}
	}
	else {
		if (jour != 30) {
			demain_jour = demain_jour + 1 ;
		}
		else {
			demain_jour = 1 ;
			demain_mois = demain_mois + 1 ;
		}
	}
}
if ((mois < 8) && (mois != 2)) {
	if (mois % 2 == 0) {
		if (jour != 30) {
			demain_jour = demain_jour + 1 ;
		}
		else {
			demain_jour = 1 ;
			demain_mois = demain_mois + 1 ;
		}
	}
	else {
		if (jour != 31) {
			demain_jour = demain_jour + 1 ;
		}
		else {
			demain_jour = 1 ;
			demain_mois = demain_mois + 1 ;
		}
	}
}
if (mois == 2) {
	if (jours_annee == 366) {
		if (jour != 29) {
			demain_jour = demain_jour + 1 ;
		}
		else {
			demain_jour = 1 ;
			demain_mois = demain_mois + 1 ;
		}
	}
	else {
		if (jour != 28) {
			demain_jour = demain_jour + 1 ;
		}
		else {
			demain_jour = 1 ;
			demain_mois = demain_mois + 1 ;
		}
	}
}
cout << "Demain, nous serons le " << demain_jour << "/" << demain_mois << "/" << demain_annee << "." << endl ;


return(0);
}
