#include <iostream>
#include <cmath>
using namespace std ;//Nicolas Collinet groupe 243L Le rôle de ce programme est de trouver le plut petit nombre premier supérieur ou égal au nombre fourni par l'utilisateur  (réponse au 2.7)
	bool nb_premier(int p) {//fonction qui permet de vérifier si un nombre est premier
	    int i;
		for (i=2; i<=sqrt(p); i++) {//on vérifie si le nombre est divisible
		    if (p%i==0) {
		        return false;
		    }
		}
	    return true;
	}
	int nb_min(int p) {//fonction qui permet de trouver le plus petit nombre premier supérieur ou égal à p
		while (nb_premier(p)==false) {//on continue tant que le nombre n'est pas premier
			p=p+1;
		}
	    return p;
	}
	
	
int main()
{
	int n;
	do {
	    cout << "Entrez un nombre strictement supérieur à 1 : ";//demande d'un entier valide à l'utilisateur 
	    cin >> n;
	} while (n<=1);
	cout << "Le plus petit nombre premier supérieur ou égal à " << n << " est " << nb_min(n) << "." <<endl;//renvoi du résultat à l'utilisateur
	return (0);
}
/*Tests:
 * 5 renvoie le plus petit nombre premier supérieur ou égal à 5 est 5. (vérification que l'algorithme fonctionne dans des conditions normales)
 * 2 renvoie Le plus petit nombre premier supérieur ou égal à 2 est 2.
 * 18945 renvoie Le plus petit nombre premier supérieur ou égal à 18945 est 18947.(vérification que l'algorithme ne renvoie pas seulement le nombre tel quel)
 * 1 renvoie Entrez un nombre strictement supérieur à 1 : 1
 * -5 renvoie entrez un nombre strictement supérieur à 1: (vérification que l'algorithme redemande bien un nombre compris dans l'intervalle demandé)
 * 2,1 renvoie Le plus petit nombre premier supérieur ou égal à 2 est 2.(vérification que l'algorithme ne tienne pas compte des décimales)
 * On a donc un algorithme qui marche,après vérification,18947 est bien premier.
 */

