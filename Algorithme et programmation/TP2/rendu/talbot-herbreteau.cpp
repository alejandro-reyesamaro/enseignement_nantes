/* talbotherbreteau.cpp - auteur: Celine HERBRETEAU e166431D et Clarisse TALBOT e163747L
Role : affiche le plus petit nombre premier supérieur ou égal à un entier préalablement saisie par l'utilisateur*/

#include <iostream>
#include <cmath>

using namespace std ;

	// déclaration de la fonction permettant de savoir si un nombre est premier ou non

	bool est_premier (int n) {
		
		int i;
		for(i=2;i<= sqrt(n);++i) { //test pour savoir si un entier est premier
			if (n%i==0){
				return (false);
			}
		}
		return(true);
	}
	



	
	// algorithme
	
	int main() { 
	
		int x;

		
		do { //aucun entier négatif n'est premier, on force la saisie d'un entier valide pour algorithme
			cout<<"Saisir un entier strictement positif: ";
			cin>>x;
		} while (!(x>0));
	
	
		if (x==1) { // cas où x=1
			x=2;
		}	

		while (! est_premier(x)) { //indentation tant que x n'est pas premier
			x=x+1;
		}


	cout<<"Le nombre premier supérieur ou égal à la saisie est "<<x<<endl; //sortie
	
	return(0);
	}




/* Jeux d'essais

	cas1 -> input 6 (pas premier : 3 * 2)
		output 7
	
	cas2 -> input 7 (premier)
		output 7
	
	cas3 -> input 1 (pas premier)
		output 2

	cas4 -> input -30 (négatif : pas premier )
		input -25 (négatif : pas premier )
		input -1 (négatif : pas premier )
		input 0 (nul : pas premier )
		input 217 (pas premier 7*31)
		output 223

	cas5 -> input 123456789 ( pas premier : 9*13 717 421)
		output 123456791

remarque: la recherche de nombres premiers supérieurs à la saisie n'excède pas 10 chiffres
	  par exemple 9876543210

*/
