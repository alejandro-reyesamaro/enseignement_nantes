/*table.cpp - auteur : Danguy Leroux
Role : Algorithme qui demande à l'utilisateur un entier et affiche le plusp etit
nombre premier directement supérieur ou égal à l'entier saisi.
*/

#include <iostream>
#include <cmath>

using namespace std;

bool est_premier(int n){
int i;
for (i = 2; i <= sqrt(n); ++i) {
        if ((n%i)==0) {
                return (false);
        }
}
return (true);
}


int main ()
        {
        int x;
	cout<< "Ecrire un entier " <<endl;
	cin  >> x;
	if (x < 0) {
		x=2;
	}
        while (!est_premier(x)) {
                x=x+1;
        }
	cout << "Le nombre premier le plus proche de la valeur saisie est " << x <<endl;
        }

/*On a rentré la valeur 8 et le résultat est 11.
On a rentré la valeur 845 et le résultat est 853.
On a rentré la valeur -5 et le résultat est 2.
*/
/* Nous avons constaté que vrai et faux doivent être mis en anglais pour que le programme les reconnaisse comme booléen.
! = non
Pas de + mais << pour écrire la variable a la suite d'un message.
Le "si" vérifie que la valeur saisie est un entier positif ou s'il ne l'est pas donne 2 comme résultat car c'est le premier nombre premier.
*/
