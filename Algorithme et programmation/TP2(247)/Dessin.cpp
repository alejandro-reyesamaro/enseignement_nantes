/* Dessin.cpp - Auteurs: BOIRO Mamadou E16A476S & MARONGIU Zaccaria E165321X

Role: Dessiner une maison comme un triangle sans base au dessus d'un carré

Précondition: La dimension doit être un nombre impair
*/

#include <iostream>

using namespace std;

/*Procedure tracer_ligne --------------------------------------------
Rôle: affiche nbe espaces, gche, (nb-2) fois milieu puis dte
*/
void tracer_ligne(int nbe, char gche, char milieu, char dte,int nb)
{

	string ligne;
	int i;
	ligne = "";

	for (i=1; i<= nbe; i++){
		ligne = ligne + " ";
	}
	
	ligne = ligne + gche ;

	for (i=2; i<= nb-1; i++){
		ligne = ligne + milieu ;
	}
	
	ligne = ligne + dte ;
	cout << ligne << endl;
}

/* Procedure carre --------------------------------------------------
Role: Tracer un carre de dimension taille en utilisant tracer_ligne
*/
void carre(int taille){

	int i;
	i = 2;
	tracer_ligne( 0, '+', '-', '+', taille) ;
	while (i <= taille-1) {
		tracer_ligne(0, '|', ' ', '|', taille) ;
		i = i + 1;
	}
	tracer_ligne( 0, '+', '-', '+', taille) ;
}

/*Procédure triangle -----------------------------------------------
Rôle: Tracer un triangle sans base de dimension taille en utilisant la procedure tracer_ligne
*/
void triangle(int taille) {
	int m, debut ;
	/* m nbre espaces milieu, debut nb espaces debut */
	debut = (taille - 3) / 2 ;
	m = 3 ;
	tracer_ligne(debut, ' ', '*', ' ', m) ;
	while ( debut >= 0) {
		tracer_ligne(debut, '/', ' ', '\\', m);
		debut = debut - 1;
		m = m + 2;
	}
}

/*Procédure maison --------------------------------------------------
Role: Tracer une maison de dimension taille en utilisant les procedures triangle puis carre
*/
void maison(int taille) {
	triangle(taille) ;
	carre(taille);
}


//Programme principal -----------------------------------------------
int main()
{	
	int nb;
	cout << "Entrez un nombre impair svp: ";
	cin >> nb;
	maison(nb);
	return(0);
}


/* Test ------------------------------------------------------------
     Valeurs: Nombres pairs ( 8, 28, 208 )
     Résultats: Il y a un decalage, mauvais alignement.
	
     Valeurs: Nombres impairs ( 5, 25, 205 )
     Résultats: Il n'y a aucun decalage, alignement parfait.

A partir de la valeur 209, l'ecran ne peut pas afficher la totalité de la maison, on ne voit qu'une partie d'elle.

Il faut imperativement que les valeurs soient impaires. 
*/
	


