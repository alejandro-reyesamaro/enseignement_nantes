//MOIZEAU Laura
//MERAND Zénaïde 
//243 K/L

#include <iostream>
#include <cmath>

using namespace std;

//Exercice 2.7 (prems)

// fonction prems

//Rôle: fonction qui permet de calculer un nombre premier 

   bool est_prems (int n) {
   int i;

	for (i = 2; i <= sqrt(n); i++) {
	    if (n%i==0) {
		return (false);
       }  
    }
 	return (true);
}

// Difficulté rencontré : penser à traduire vrai et faux en anglais

int main()
{

//Algorithme prem's

//Role de l'algorithme : premièrement savoir si le nombre choisi est un nombre premier, si c'est le cas alors l'algorithme affiche celui-ci et si ça ne l'est pas alors il donne le nombre premier le plus proche du nombre saisi. int x;
   
   cout << "saisir un entier" << endl;
   cin >> x;
      if (x<= 0) {
	cout << "Le nombre premier le plus proche est 2" << endl;
	}
      else {
          while (!est_prems(x)) {
	     x=x+1; 
       }
      cout << "Le nombre premier le plus proche est " << x << endl; 

  }
 
}

//penser a ne pas mettre de "+" entre la phrase et x mais des <<.



