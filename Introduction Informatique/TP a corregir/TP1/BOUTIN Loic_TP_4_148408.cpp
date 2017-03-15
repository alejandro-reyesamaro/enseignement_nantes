/* 143_BOUTN+CLOUET_TP_4 - auteur : P.Clouet et L.Boutin
Role : 	dit si l'année est bissextile ou non
	donne le nombre de jours dans le mois donné
	indique la date du lendemain
*/

#include <iostream>

using namespace std;

int main ()
{
	int jo, mo, an, jof, jo2, mo2, an2; //Déclaration des variables

cout << "Le jour ?" << endl; // Demande le jour correspondant
cin >> jo;
cout << "Saisir le nombre correspondant au mois ?" << endl; //Demande le mois correspondant
cin >> mo;
cout << "L'année ?" << endl; //Demande l'année correspondantes
cin >> an;

if (((an % 4 == 0) && (an % 100 != 0)) || (an % 400 == 0) ){ //Test sur l'année bissextile ou non
	cout << "L'année est bissextile" << endl;
	jof = 29;
}else{
	cout << "L'année n'est pas bissextile" << endl;
	jof = 28;
}

if ((mo == 1) || (mo == 3) || (mo == 5) || (mo == 7) || (mo == 8) || (mo == 10) || (mo == 12)){ //Test sur le mois de l'année
	cout << "Il y a 31 jours dans ce mois" << endl;
}else{
	if (mo == 2){ //Test sur février
		cout << "Il y a " << jof << " dans ce mois" << endl;
}
	cout << "Il y a 30 jours dans ce mois" << endl;
}

jo2 = jo + 1; //Attribution des variables du jour d'après
mo2 = mo;
an2 = an;

if (jo2 == 32){ //Test sur les mois en 31 jours
	jo2 = 1;
	mo2 = mo + 1;
	if (mo2 == 13){
		mo2 = 1;
		an2 = an + 1;
}
}

if ((jo2 == 31) && ((mo == 4) || (mo == 6) || (mo == 9) || (mo == 11))){ //Test sur les mois en 30 jours
	jo2 = 1;
	mo2 = mo + 1;
}

if ((jo2 > jof) && (mo == 2)){ //Test sur les février
	jo2 = 1;
	mo2 = 3;
}

cout << "Le jour d'après sera le " << jo2 << " / " << mo2 << " / " << an2 << endl; //Annonce du jour d'après

return(0);
}

/*
Tests d'essais :

30 / 04 / 1996 : Bissextile , 30 , 01 / 05 / 1996
*/

