/* tp2_terrien_dasan.cpp auteurs: Lea_Terrien Miryam_Dasan 
role: afficher le plus petit nombre premier directement superieur ou egal a lentier saisi
*/

#include <iostream>
#include <math.h>

using namespace std;

/* Tests
5 premier : 5
6 non premier : 7
65535 grand nombre non premier : 65537
Cas specifiques
1 non premier : 2
0 non premier : 2
*/



//-------------------------------
// fonction qui détermine si un nombre est premier 

bool est_premier (int n) {   

      int i; 

      for (i=2; i<= sqrt(n); i++) {
    	     if (n % i == 0) {
		     return (false);
	      }
      }
	
      return (true);
 }

//-------------------------------
//fonction principale

int main () {

     int nb; 

     // Saisie d un entier par lutilisateur

     cout << "veuillez saisir un entier" << endl; 
     cin >> nb;

     // Recherche du nombre premier directement superieur ou egal a nb

     if (nb==0 || nb==1) {
           nb = 2;
     } else {

           while (! est_premier (nb)) {
                nb = nb + 1;
           }
     }

     // Affichage du nombre premier trouve

     cout << "le plus petit nombre premier trouve est " <<  nb  << endl;

     return (0);
}
   
