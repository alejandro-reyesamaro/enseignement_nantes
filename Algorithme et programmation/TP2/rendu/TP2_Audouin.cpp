/* Exercice 2.7 TP2.cpp -Auteur : Audouin Florentin groupe 243
Role : Afficher le plus petit nombre premier directement supérieur ou égal à l'entier saisi)
*/



#include<iostream>
#include<string>
#include<math.h>
using namespace std;

bool est_premier(int n){ // fonction pour trouver si la saisie est un nombre premier ou pas
	
	int i;
	
	for(i=2; i<= sqrt(n);++i) // savoir si un nombre inferieur à sa racine divise n et i=2 car 2 est le plus nombre premier et 1 divise tout le monde
	{
		if((n%i)==0)
		{// si n admet un diviseur autre que 1 et lui même
	return(false);} // end if 

	

	}// end for
return (true);
}// fin fonction



// fonction principale
int main()
{
	int X;

	cout<<"quel est l'entier?"<<endl;
	cin>>X;// nombre saisie supérieur à 1

	while(! est_premier(X)){ // si la saisie n'est pas première alors saisie=saisie+1 jusqu'au moment ou saisie devient premier
	X=X+1;
	} // end while
	cout<<" le premier entier premier supérieur ou égal à n est "<<X<<endl;
}



/* Case 1 --> input : "3"
	  --> output : "3" 
Or 3 est un nombre premier donc le résultat obtenu est 3 directement.


  Case 2  --> input : "1"
	  --> output : "1"  
 Le résultat obtenu est 1 or 1 n'est pas un nombre premier donc l'algorithme a un problème pour n=1


 Case 3 --> input :"6"
	    output : "7"
Or 6 est divisible par 2 et 3 donc 6 n'est pas un nombre premier et nous obtenons 7 en résultat et 7 est le premier nombre premier supérieur ou égal à 6.


 Case 4 --> input :"0"
	--> output :"0"

Or 0 n'est pas un nombre premier et on obtient 0 en résultat or le premier entier premier supérieur ou égal à 0 est 2 donc il y a un problème.


 Case 5 --> input: "la"
	--> output: "0"

l'algorithme rend 0 comme résultat si la saisie n'est pas un nombre.

 Case 6 --> input: "-22"
	--> output: " -22"
Donc lorsqu'un nombre négatif est saisie, alors le résultat obtenu est le nombre saisie or -22 n'est pas un nombre premier donc l'algorithme fonctionne seulement avec les entiers naturels
*/






