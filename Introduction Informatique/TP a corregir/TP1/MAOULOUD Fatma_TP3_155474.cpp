#include <iostream>
using namespace std;

/*MAOULOUD Fatma 
FARDEHEB Amina
TP3 année bissextile avec date du lendemain*/


//Declaration de la fonction est_bissextile qui rend un booléen.

bool est_bissextile(int a){

if (((a%4 == 0) && (a%100!=0)) || (a%400==0)) {
return (true);
}
else {
return (false);
}
}


int main()
{
int annee; 
int mois;
int jour;

cout << "Saisissez l'année"; 
cin >> annee; 
cout << "Saisissez le mois";
cin >> mois;
cout << "Saisissez le jour";
cin>> jour;

if (est_bissextile(annee)) {
cout << "l'année" << annee << " est bissextile.";
}
else {
cout << "l'année" << annee << " n'est pas bissextile.";
}
if ((mois == 1)||(mois == 3) || (mois == 3)|| (mois == 5) || (mois== 7)|| (mois ==8) || (mois ==10) || (mois == 12)) {
cout << "il y'a 31 jours dans le mois " << mois;
if (jour < 31) {
jour ++;
}
else{if (mois != 12) {
mois++;
}
else {
mois = 1;
annee ++;
}
}
}
else {
	if ((mois==4)||(mois==6) || (mois==9)|| (mois==11))
	{
		cout << "il y'a 30 jours dans le mois " << mois;
		if (jour < 30) {
			jour ++;}
		else { mois++;}
	}
}
	if (est_bissextile(annee)) {
		cout << "il y'a 29 jours dans le mois " << mois;
		if (jour < 29) {
			jour ++;}
		else { 
			jour = 1;
		}
	}
	else { 
		if (jour != 28) 
		{
			jour++;
		}
		else {
			jour = 1;
		}
	}

	cout << "il y'a 28 jours dans le mois de " << mois;
    cout << "la date de demain est le : " << jour << "//" << mois << "//" << annee;
    return (0);
}





