// 243 - Charpentier Jodie
//TD 2 Exo 2.7


#include <iostream>
#include <cmath>

using namespace std ;

// SS-Algo : fonctions prems = booleen
// Role : permet de calculer un nombre premier
bool prems (int n)
{ 
  int i;
  for ( i=2 ; i<=sqrt(n); ++i)
   {
      if (n%i==0)
        {
          return (false);
          // faux doit etre ecrit en anglais
         }
    }
  return (true);
  // vrai doit etre ecrit en anglais
}
   
// Algo : nombre premier le plus proche 
// Role : permet d'appeler un nombre et trouver le nombre premier le plus proche
int main()
{
  int x;
  cout << "Ecrire un entier " << endl;
  cin >> x;
// il faut vérifier que le nombre saisie est positif et s'il est négatif il prend la valeur 2 car il est la premier nombre premier
  if ( x <= 0 )
   {
     x=2;
    }
  while (!prems(x))// "!" = non
   {
     x=x+1;
    }
  cout << "le nombre premier le plus proche est " << x << endl;
// pas de "+" pour ajouter x mais "<<"
}



