/* Groupe 243 
HERBERT Calvin 	 E16C002B
RAMBAUD Baptiste E165795M
Feuille TP n°2
Feuille TD n°2
Exercice 2.7
Rôle : Demander à l'utilisateur un entier et affiche le plus petit nombre entier directement supérieur ou égal à l'entier saisi. */

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Fonction qui détecte si un nombre est premier ou pas
bool est_premier( int n )
{
	int i;
	for ( i = 2; i <= sqrt(n); i++ ){
		if ( n % i == 0 ){
			return false;
		}
	}
	return true;
}

//Renvoie le nombre premier tout en prenant en compte les entiers inférieurs ou égaux à 1.
void nombre_premier( int& nombre )
{
	// Résolution pour un entier inferieur ou égal à 1. 
	if ( nombre <= 1 ){
		nombre = 2;
	}
	
	// Trouve le nombre premier
	while ( ! est_premier(nombre)){
		nombre += 1;
	}
}

// Algorithme Prems'
int main ()
{
	// Variable
	int nombre;
	
	// Saisie
	cout << "Saisissez un nombre : ";
	cin >> nombre;
	
	// Programme
	nombre_premier( nombre );
	cout << "Le plus petit nombre premier directement supérieur est : " << nombre << "." << endl;
}

/* JEU D'ESSAIS

Test 1 :
input : -5
output : Le plus petit nombre premier directement supérieur est : 2.

Test 2 :
input : 1
output : Le plus petit nombre premier directement supérieur est : 2.

Test 3 :
input : 5
output : Le plus petit nombre premier directement supérieur est : 5.

Test 4 :
input : 70
output : Le plus petit nombre premier directement supérieur est : 71.

Conlusion :
Notre programme fonctionne pour tout nombre pouvant être contenu dans une variable de type int.

*/



















