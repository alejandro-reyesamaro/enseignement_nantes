/* exo 2.7.cpp TP2- auteurs: ROCHER C. et GUEHO A.
Role : affiche le plus petit nombre premier directement superieur ou
égale à l'entier saisi par l'utilisateur */ 

//On utilise la bibliothèque cmath pour pouvoir utiliser la fonction sqrt (racine carrée)
#include <iostream>
#include <cmath>

using namespace std;

/*On utilise une procédure (exercice précédent) qui force à entrer un 
entier strictement positif*/

void positif (int &nombre){
do
	{cout<<"Saisir un entier strictement positif ";
	cin>>nombre;
	}
while (!(nombre>0));
}
	
/*On crée une fonction qui renvoie vrai si le nombre est premier, faux s'il ne l'est pas
Pour cela, on cherche si un des entiers entre 2 et la racine carrée du nombre le divise */

bool est_premier (int n) {
	int i;
	for (i=2; i<=sqrt(n); i++) {
		if (n%i==0) {
			return(false);
		}
	}
	return(true);
}

//On fait saisir l'entier à l'utilisateur.
/*On utilise la fonction avec le nombre saisi dans l'agorithme principal
 au sein d'une boucle "tant que" qui, à partir du nombre saisi, tant 
 que la fonction renvoie faux, la boucle fait ajouter 1 au nombre testé.
 */


int main () {
	int x,w;
	positif(x);
	w=x;
	while (!est_premier(w)){
		w=w+1;
	}
	cout<<endl<<"Le plus petit nombre premier directement supérieur ou égal à "<<x<<" est: "<<w<<endl;
	return(0);
}


/*
 * test 1 : on entre -5 : on doit ressaisir un nombre car -5 est négatif
 * test 2: on entre 0 : on doit ressaisir un nombre car 0 n'est pas strictement positif
 * test 3: on entre 6 : on obtient 7. en effet, 7 est le plus petit nombre premier après 6
 * test 4: on entre 23 : on obtient 23
 * on remarque que l'algorithme a une limite : pour tous les nombres saisis supérieurs à 2147483647, l'algorithme affiche 2147483647  
 Finalement, l'agorithme fonctionne bien jusqu'à une certaine limite */
