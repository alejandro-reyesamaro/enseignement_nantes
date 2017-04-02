/* 243_BOUTIN+CLOUET_BOUTIN CLOUET.cpp - auteur : P.Clouet et L.Boutin 
Exercice 3.6 : Permet de décaler circulairement de n cases les valeurs d'un tableau
*/

#include <iostream>

using namespace std;

const int N = 100;
typedef struct { int contenu[N]; int nb; } T_tabEnt;

T_tabEnt Saisie_tableau()
{
	T_tabEnt tab;
	int ind;
	cout << "Un nombre de cases?" << endl;
	cin >> tab.nb;
	ind = 0;
	while (ind < tab.nb)
	{
		cout << "Saisissez une valeur pour la case " << ind+1 << " du tableau." << endl;
		cin >> tab.contenu[ind];
		ind++;
	}
	return tab;
}

void Affiche_tableau(T_tabEnt tab)
{
	int ind;
	for (ind = 0; ind <= tab.nb - 1; ind++)
	{
		cout << tab.contenu[ind] << " ";
	}
	cout << endl;
}

void Decalage (int decal, T_tabEnt& tab)
{
	int ind; 
	T_tabEnt tempo;
	// Recopie du tableau
	for (ind = 0 ; ind <= tab.nb - 1; ind ++)
	{
		tempo.contenu[ind] = tab.contenu[ind];
	}
	// Restitution avec décalage
	for (ind = 0 ; ind <= tab.nb -1; ind ++)
	{
		tab.contenu[(ind + decal) % tab.nb] = tempo.contenu[ind];
	}
}

void Decalage2 (int decal, T_tabEnt& tab)
{
	int ind;
	int tempo;

	if (decal != 0)
	{
		tempo = tab.contenu[tab.nb-1];

		for (ind = tab.nb - 1 ; ind >= 1 ; ind --)
		{	
			tab.contenu[ind] = tab.contenu[ind - 1];
			cout << ind << endl;
		}

		tab.contenu[0] = tempo;

		Decalage2(decal - 1, tab);

	}
}

int main()
{

T_tabEnt tableau;
int decalage;

tableau = Saisie_tableau();

cout << "Un nombre de cases à décaler ?" << endl;
cin >> decalage;

Decalage2(decalage, tableau);
Affiche_tableau(tableau);

return(0);
}
