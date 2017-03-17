/*Algo2.2(Dessin):SECK Abdoulahat
Role: Dessine une maison comme un triangle sans base au-dessus d'un carre
*/
#include <iostream>
#include <string>

using namespace std;


//---------------------------------------------------------------
// rôle : Permet de tracer des lignes en prenant des parametres 
// trace une ligne de longueur taille, qui commence par gche avec un milieu et se termine par dte,
void tracer_ligne( int nb, char gche, char  milieu, char dte, int taille)
{
	string ligne;
	int i;

	ligne = "";
	for ( i = 1; i <= nb; i = i+1 ) {
		ligne = ligne + " ";
	}
	ligne = ligne + gche;
	for ( i = 2; i <= taille - 1; i = i+1 ) {
		ligne = ligne + milieu;
	}
	ligne = ligne + dte;
	cout << ligne << endl;
}

//---------------------------------------------------------------
// rôle : Permet de tracer un carre de cote taille

void carre( int taille)
{
	int i;
	char milieu;
	
	i = 0;
	tracer_ligne( 0 , '+', '-', '+', taille );
	while ( i != (taille-2)){
		tracer_ligne( 0, '|', ' ', '|', taille );
		i = i + 1;
	}
	tracer_ligne(0, '+', '-', '+', taille);
}
//---------------------------------------------------------------
// rôle : Permet de tracer un triangle sans base

void triangle( int base)
{
	int i;
	int moitie;
	
	moitie= (base - 1) / 2;
	tracer_ligne( moitie - 1, ' ', '*', ' ', 3);
	//milieu = ' ';
	for (i=1; i <= moitie; i = i+1) {
		tracer_ligne(  moitie - i, '/', ' ', '\\', (2 * i + 1) );
	}
}

//---------------------------------------------------------------
// rôle : Permet de construire une maison comme un triangle sans base
//		  au-dessus d'un carré de cote
// Sous condition la variable cote ne prend pas de valeur negatif
#include <iostream>
#include <string>

using namespace std;

int main ()
{
	int cote;

	cout << "cote ? ";
	cin >> cote;
	triangle(cote);
	carre(cote);
}

// lorsqu' on saisie 5 ça affiche une maison comme un triangle sans base
//		  au-dessus d'un carré de cote 5
// lorsqu' on saisie -5 ça affiche rien
