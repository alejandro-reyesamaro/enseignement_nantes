/* 27.cpp - auteur : Boudeville-Raimbaut Orlane, Raffin Valentin groupe 243.
 * TP 2 Exercice 2.7
 * Role : affiche le plus petit nombre premier directement supérieur ou égal à un entier saisi 
*/

#include <iostream>
#include <cmath>

using namespace std;

// Fonction qui verifie si le nombre saisi est premier
bool prem ( int n )
{
	int i;
	if (n<= 1)
	{
		return (false);
	}
	else
	{		
		for (i=2 ; i<=sqrt(n) ; i++) // verifie si le nombre est premier
		{
			if (n % i == 0)
			{ 
				return (false);
			}
		}
		return (true);
	}
}

// Algorithme
int main()
{
	int x;
	cout << "saisir un entier" << endl; // demande de saisie
	cin >> x;
	if (prem(x))
	{
		cout << x << " est un nombre premier." << endl;
	}
	else
	{
		cout << "Le plus petit nombre premier directement supérieur à " << x;
		while (!(prem (x))) // incrementer x si il n'est pas premier
		{
			x=x+1;
		}
		cout << " est ";
		cout << x << endl; // afficher le resultat
	}
} 


/* Jeux de Test :
 * Input : "-3"  Output "Le plus petit nombre premier directement supérieur à -3 est 2" test de -3 car c'est un nombre negatif et un nombre premier est forcement positif
 * Input : "0"   Output "Le plus petit nombre premier directement supérieur à 0 est 2"  test de 0 car c'est la limite entre les nombres positifs et negatifs
 * Input : "1"   Output "Le plus petit nombre premier directement supérieur à 1 est 2"  test de 1 car c'est un entier positif mais un nombre premier est strictement superieur à 1
 * Input : "59"  Output "59 est un nombre premier" test de 59 car c'est premier
 * Input : "57"  Output "Le plus petit nombre premier directement supérieur à 57 est 59" test de 57 car ce n'est pas un nombre premier
 * Input : "3586687635465" Output "2147483647 est un nombre premier." test de 3586687635465 car il depasse la memoire du int
*/
