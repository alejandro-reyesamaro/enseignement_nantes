/*Marie PEAN Gauthier THURIN 243*/
#include <iostream>
#include <cmath>
using namespace std;
int est_preums(int n)// Fonction qui permet de déterminer si un entier est premier ou non.
{
	int i;
	
	if ((n>=2)||(n==-1))// On considère que les entiers négatifs, 0 et 1 ne sont pas premiers.
	{
		for (i=2;i<=sqrt(n);i++)//On cherche à savoir si il y a un troisième diviseur à n.
		{
			if (n%i==0)
			{
				return  false;
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}

// Algorithme:Preums

int main ()
{
	int ent;
	cout<<"Saisir un entier ";
	cin>>ent;
	cout<<ent<<endl; //Si l'utilisateur ne rentre pas un entier on peut voir comment la machine le traduit en entier.
	while (!est_preums(ent))
	{
		ent=ent+1;
	}
	cout<<"Le plus petit nombre premier directement supérieur ou égal est "<<ent<<endl;
}

/*Jeux d'essais:
 Pour 0 on obtient 2, car 0 n'est pas considéré comme un nombre premier
 Pour 1 on obtient 2 pour la même raison que pour le 0
 Pour -3 on obtient 2 car les entiers négatifs sont aussi divisible par -1 donc ils ne sont pas premiers
 Pour 8 on obtient 11 et pour 2 on obtient 2.  
 Pour -1 on obtient -1*/
