/* groupe :243k, NGOM MOUSTAPHA , TDTP2, exo2.7 */

#include <iostream>
#include <cmath>
using namespace std;


bool premier( int n) // fonction qui permet de savoir si un entier est premier ou pas 
  {
	  int i;
	  for( i=2; i<= sqrt(n) ; i++ ) 
	     {
		   if( n % i == 0) 
			 {
				 return false; 
			 }
		}
		return true;
		
	}
int main() //algo qui utilise la fonction pour troouver un entier >= à l'entier saisi
{
	int entier ;
	cout<< "donnez moi un entier";
	cin>>entier ;
	while (! premier(entier)) /* boucle qui permet de reprendre la fonction "premier" 
		jusqu'a trouver un nombre premier*/
	{ 
		
		entier = entier + 1 ;
	}
	cout<< "le plus petit entier superieur ou égale à l'entier saisi est  "<< entier<< endl; /* sortie de l'entier obtenu, ça sera soit l'entier
	 soit le premier nombre premier superieur à l'entier*/
	return(0);
	 
			 
 }
 /* tout les entiers testés sont bon sauf quue lorsqu'on saisi un entier beaucoup trop grand l'ordinateur n'arrive pas à faire  */
 
