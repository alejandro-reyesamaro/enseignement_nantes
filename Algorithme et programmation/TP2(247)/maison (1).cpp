/* maison.cpp − auteur : Quentin & Erwan
Role :  dessine une maison. 
test: avec 4
resultat: 
+- +
|  |
|  |
+- +
conclusion : ne fonctionne pas
*/


#include <iostream>
#include <string>

using namespace std ;


//---------------------------
//Sous Algo


// −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
// Role de la procédure: trace une ligne avec des caractères ou alors avec un nombre d'espaces donnés

void tracerligne (int nbe, char gauche, char milieu, char droite, int taille) {

  string ligne;
  int i;

  ligne = milieu;

  for (i=0; i <= nbe; ++i){
     ligne= ligne + " ";
  }

  ligne= gauche + ligne;

  for (i=2; i<= nbe-1; ++i) {
     ligne= ligne + milieu;
  }

  ligne= ligne + droite  + '\n';
  
  cout << ligne ; 

}

// −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
// Role de la procédure: trace un carré de coté taille

void carre (int taille){

  int i; 

  i = 2;
  tracerligne(0, '+', '-' , '+' , taille -2); 

  while (i <= (taille-1) ) {
     tracerligne(0 , '|', ' ', '|', taille- 2);
     i = i + 1;
  }

  tracerligne(0, '+', '-', '+', taille - 2);
}

// −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
// Role de la procédure: trace un triangle de coté taille

void triangle (int taille) {

  tracerligne(1, ' ', '*', ' ', taille - 2);
  tracerligne(1, '/', ' ', '\\', taille - 2);
  tracerligne(0, '/', ' ', '\\', taille - 2);
}


// −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
// fonction principale
int main ()
{
  int taille;

  cout << "taille?" ;
  cin >> taille ;
  triangle (taille);
  carre (taille);
}







