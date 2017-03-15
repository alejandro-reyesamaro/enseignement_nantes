/* Exercice2.7 TP-2.cpp - auteur : Simon Jadeau_Jonas O'Neill 243K
Role: Affiche le plus petit nombre premier directement supérieur ou égal à l'entier saisi.
*/

#include <iostream>
#include <string>
#include <math.h> 

using namespace std;


bool est_prem(int n) //La fonction est_prem retourne "vrai" pour le plus petit nombre premier avec l'entier saisi.
{
	int i;
	for (i=2;i<= sqrt(n); i++)
	{
	if (n%i==0){
	return false;
		}	
	}
	return true;
}

int main() 				// Cet algorithme permet de connaître le plus petit nombre premier supếrieur ou égal à l'entier saisi
{
	int x;
	cout << "Saisir un nombre entier : " ;
	cin >> x; 			// On demande à l'utilisateur de saisir un entier
	if (x<=1) {
		x = 2; 			// Traitement du cas où x est inférieur à 1
		} else { 	    // Fin du si, début du sinon
	while (!est_prem(x)){// Utilisation de la fonction est_prem pour réaliser l'algorithme
	x = x+1;
			   } 		// Fin tant que
	} 					// Fin sinon
	cout << "Le plus petit nombre premier directement supérieur ou égal à l'entier saisi est : " << x << endl;
}

/* Case 1 : 
   input "36"
   output"37"
Lorsque l'on saisi "36", l'algo renvoi "37"qui est le plus petit nombre premier supérieur ou égal à l'entier saisi.   
   
   Case 2 : 
   input "-5"
   output "2"
Lorsque l'on saisi un entier négatif, ou en général, un nombre inférieur ou égal à 1, le plus petit 
nombre premier supérieur ou égal à ce nombre est donc 2.

   Case 3 : 
   inpupt "chantier"
   output "2"
Lorsque une chaine de caractère, un réel, ou tout autre objet qui n'est pas un entier est saisi, l'algorithme traitera l'objet comme 
étant un 0. Il renvoiera alors 2, comme vu dans le cas précédent.

   Case 4 : 
   input "41"
   output "41"
Lorsqu'un nombre premier est saisi, l'algorithme renvoie le même nombre premier, ce qui respecte l'énoncé.
*/
