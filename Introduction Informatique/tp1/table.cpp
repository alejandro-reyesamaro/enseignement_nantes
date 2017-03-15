/* table.cpp - auteur: C. Enguehard
Role : affiche la table de multiplication choisie par l'utilisateur.
*/

#include <iostream>

using namespace std;
// −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
// fonction principale

int main()
{
	int nombre;
	int table;	
	// saisie de la table
	cout << "Quelle table de multiplication afficher ? ";
	cin >> table;
	// affichage de la table
	for ( nombre = 1; nombre <= 10; nombre++) {
		cout << nombre << " x " << table << " = " << nombre * table << endl;
	} // for
	return (0);
}
