/*  maison.cpp Auteurs: MOULAZEM Younes E161413Z et HUET Mathieu E15F880X
 Rôle: dessine une maison de taille saisie par l'utilisateur
*/

#include <iostream>

using namespace std;

string tracer_ligne_carre (int cote, int numLigne){
	// retourne la 'numLigne'-ième ligne du carré de longueur de côté 'cote'
	
	string ligne = "";
	
	if( (numLigne == 1) || (numLigne == cote) ){ // cas de la première et de la dernière ligne
		ligne += '+';
		int i;
		
		for(i = 1 ; i <= (cote-2) ; i++){
			ligne += '-';
		}
		
		ligne += '+';
	} else { // cas général des autres lignes
		ligne += '|';
		int j;
		
		for(j = 1 ; j <= (cote-2) ; j++){
			ligne += ' ';
		}
		
		ligne += '|';
	}
	return ligne;
}

string tracer_ligne_triangle (int base, int numLigne){
	// retourne la 'numLigne'-ième ligne du triangle de longueur de base 'base'
	
	string gauche = "";
	string droite = "";
	string milieu = "";
	int i;
	
	if(numLigne == 1){ // cas de la première ligne
		milieu = "*";
		
		for ( i = 1 ; i <= (base-1)/2 ; i++ ){
			gauche += ' ';
			droite += ' ';
		}
		
	} else { // cas général des autres lignes
		milieu = " ";
		
		for ( i = 1 ; i <= (base-1)/2 ; i++ ){
			if(i == (numLigne-1)) {
				gauche = '/' + gauche;
				droite += '\\';
			} else {
				gauche = ' ' + gauche;
				droite += ' ';
			}
		}
	}
	return (gauche + milieu + droite);
}

string dessinCarre (int cote) {
	/* retourne le carré de longueur de côté cote 
	( où cote est le nombre de caractères par ligne et le nombre de lignes) */
	
	string carre = "";
	int nligne;
	
	for ( nligne = 1 ; nligne <= cote ; nligne++ ){
		carre += tracer_ligne_carre(cote, nligne);
		carre += '\n';
	}
	
	return carre;
}

string dessinTriangle (int base) {
	 // retourne le triangle sans base de longueur de base 'base'
	 
	 string triangle = "";
	 int nLigne;
	 
	 for ( nLigne = 1 ; nLigne <= ((base+1)/2) ; nLigne++){
		 triangle += tracer_ligne_triangle( base, nLigne);
		 triangle += '\n';
	 }
	 
	 return triangle;
}

int main () {
	int longueurCarre = 0;
	
	do {
	cout << "Entrez la longueur impaire du côté du carré: ";
	cin >> longueurCarre;
	} while (!(longueurCarre % 2 == 1)); // vérification de saisie ( longueurCarre doit être impair )
	
	cout << dessinTriangle(longueurCarre);
	cout << dessinCarre(longueurCarre) << endl;
}

/* Jeux de tests:

Entrez la longueur impaire du côté du carré: 13
      *      
     / \     
    /   \    
   /     \   
  /       \  
 /         \ 
/           \
+-----------+
|           |
|           |
|           |
|           |
|           |
|           |
|           |
|           |
|           |
|           |
|           |
+-----------+

----------------------------------------------------

Entrez la longueur impaire du côté du carré: 4
Entrez la longueur impaire du côté du carré: 6
Entrez la longueur impaire du côté du carré: 8
Entrez la longueur impaire du côté du carré: 10
Entrez la longueur impaire du côté du carré: 11
     *     
    / \    
   /   \   
  /     \  
 /       \ 
/         \
+---------+
|         |
|         |
|         |
|         |
|         |
|         |
|         |
|         |
|         |
+---------+

*/

/* Conclusion: Ce programme permet donc bien d'afficher avec des caractères ASCII un dessin analogue
à la représentation en deux dimensions d'une maison de taille variable et définie par l'utilisateur.
Seule contrainte: un nombre impair de caractères par ligne afin de respecter la symmétrie
par rapport au sommet du dessin. */
