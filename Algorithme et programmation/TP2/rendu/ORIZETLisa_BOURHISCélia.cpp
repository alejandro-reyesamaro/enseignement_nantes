/* premstp2.cpp groupe 243 Célia BOURHIS et Lisa ORIZET TD2/TP2 Exercice 2.7
rôle : algorithme qui affiche le plus petit nombre premier directement supérieur 
ou égal à un entier x saisi.
*/



#include <iostream>
#include <cmath>

using namespace std;

//fonction booléenne qui vérifie si un nombre est premier 

bool est_premier(int n)
{
	int i;


	for (i=2;i<=sqrt(n);++i) {	
		if ((n%i)==0) {
			return false;
		} //if
	} //for
	return true;
	
}


//---------------------------------------------------------

/* algorithme utilisant la fonction est_premier afin d'afficher le 
plus petit nombre premier qui est supérieur ou égal à un entier x saisi. */

int main ()
{

	int x;

//Saisie de l'entier
	cout << "Saisir un entier";
	cin >> x;

//Affichage du nombre premier demandé
	while (!est_premier(x)) {
		x=x+1;
	}
	cout << "Le nombre premier recherché est " << x;

}



/* Jeux de test :
- fonction :
	> un nombre premier 
		ex : pour n=3, on obtient "true".
	> un nombre non premier
		ex : pour n=14, on obtient "false".

- algorithme :
	> un nombre premier
		ex : en saissisant x=17, on obtient "Le nombre premier recherché est 17".
	> un nombre non premier
		ex : en saissisant x=26, on obtient "Le nombre premier recherché est 29".

L'algorithme ne fonctionne que sur l'ensemble des entiers strictement positifs.
*/
		



















