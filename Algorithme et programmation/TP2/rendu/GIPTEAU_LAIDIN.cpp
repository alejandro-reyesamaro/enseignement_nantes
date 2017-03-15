/* Groupe 243 - LAIDIN Tino, GIPTEAU Thibaut - TD2, exercice 2.7
Rôle : Renvoie le nombre premier supérieur ou égal le plus proche au nombre donné par l'utilisateur. */

#include <iostream>
#include <cmath>

using namespace std;

//-------------------------------------------------------------------------

bool isprime(int n) { // évaluation du caractère premier
	
	int i;

	for(i=2;i<=sqrt(n);i++) {
		if (n%i==0) {
			return(false);
		} //if
	} //for

	return(true);
} // isprime


int nextprime(int n) { // recherche du nombre premier suivant

	if(n<=1) {
		return 2;
	} //if

	while(!isprime(n)) {
		n++;
	} //while

	return(n);
} //nextprime
	

int main() { //fonction principale
	
	int x;

	cout << "Saisissez un entier." <<endl;
	cin >>  x;
	cout << nextprime(x) <<endl;

	return 0;
} //main

/*Jeu d'essais :
		-input "2"
		-output "2"

		-input "-5"
		-output "2"

		-input "4"
		-output "5"
*/




