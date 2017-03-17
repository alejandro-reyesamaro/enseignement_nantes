//-----------------------------------
// Rôle : dessiner la maison 
//Auteurs : Portejoie Jeremie, Borisov Vadim

#include <iostream>
using namespace std;



//---------------------------------------
//tracer_ligne: procédure pour tracer une ligne avec n espaces
// devant premier caractère, de caractère de debut:cgche, 
//caractères de milieu: cmilieu de taille k, et de caractère de fin:cdrte


void tracer_ligne (int n, int k, char cgche, char cmilieu, char cdrte ){
	int i;	
	cout << ' ';
	for (i = 1; i < n; i++) {
		cout << ' ';        //ajoute n espaces devant cgche
	}	
	cout << cgche;              
	for (i = 1; i <= k-2; i++){
		cout << cmilieu;    //ajoute (taille-2) cmilieu
	}
	cout << cdrte;
	cout << endl;
}

//---------------------------------------
//carre: procédure pour dessiner le carré de coté : taille

void carre(int taille){
	int i;
	i = 0;
	tracer_ligne(0, taille, '+', '-', '+');    //trace la ligne supérieure du carré
	while (i != (taille-2)){
		tracer_ligne(0, taille, '|', ' ', '|' );  //trace les cotés du carré
		i++;
	}
	tracer_ligne(0, taille, '+', '-', '+');	  //trace la ligne inférieure du carré
}

//----------------------------------------
//procédure pour dessiner le triangle de la base: taille

void triangle(int taille){
	int nbe;
	int nbetr;
	nbe = (taille/2);       //nombre d'espaces devant premier caractère du triangle
	nbetr = 3;              //nombre d'espaces dans le triangle entre les cotés
	tracer_ligne((taille/2)+1, 0 , '*', ' ', ' ');  // tracer l'étoile au sommet

	do{
		tracer_ligne(nbe, nbetr, '/', ' ', '\\');
		nbetr = nbetr+2;  //ajoute 2 espaces pour que les bords s'écartent symétriquement
		nbe--;
	} while(!(nbe == 0));    //trace les cotés du triangle
}

//----------------------------------------
//préconditions : taille est impaire

int main()
{	
	int taille;
	cout << "Entrez une taille de votre maison: ";
	cin >> taille;
	if (taille%2 == 1){            //oblige à rentrer une taille impaire
	    triangle(taille);
	    carre(taille);
	}
	else {
	cout << "Entrez une taille impaire" << endl;
	}
	return (0);
}

//--------------------------------------
//Tests: -taille = 7, 9, 11 => dessine une maison de coté 7/9/11
//       -taille paire:8,10 => "Entrez une taille impaire"

//Résultat: on obtient la maison correctement dessinée

/*Conclusion: pour ce TP on a utilisé les procédures tracer_ligne, carre et triangle
pour obtenir le dessin de la maison.
INPUT:taille
OUTPUT:maison dessinée de coté égale à taille*/






