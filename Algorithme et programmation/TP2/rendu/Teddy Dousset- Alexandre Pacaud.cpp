//Alexandre Pacaud et Teddy Dousset groupe 243
#include <iostream>
#include <cmath>
using namespace std ;
	bool nb_premier(int p) {
	    int i;
		for (i=2; i<=sqrt(p); i++) { //un nombre est premier si on ne trouve aucun diviseur entre 2 et sa racine
		    if (p%i==0) {            // on regarde si i divise p
		        return false;
		    }
		}
	    return true;
	}
	int nb_min(int p) {
		while (nb_premier(p)==false) { // tant que le nombre testé n'est pas premier, on passe au suivant
			p=p+1;
		}
	    return p;
	}
	
	
int main()
{
	int n;
	do {
	    cout << "Entrez un nombre strictement positif : ";
	    cin >> n;
	} while (n<=0); // Saisie forcée d'un entier strictement positif
	cout << "Le nombre premier suivant ou égal de " << n << " est : " << nb_min(n) << "." <<endl;
	return (0);
}


/* JEUX D'ESSAIS

Avec n=-9
Affiche " Entrez un nombre strictement positif : "
*
Avec n=0
Affiche " Entrez un nombre strictement positif : "
* 
Avec n=29 (test avec un nombre premier)
Affiche "Le nombre premier suivant ou égal de 29 est : 29."
* 
Avec n=30 (test avec un nombre non premier)
Affiche "Le nombre premier suivant ou égal de 30 est : 31."
*/
