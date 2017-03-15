/* Groupe 243 - GENDRONNEAU P. et GUILLOTEAU L. - TPTD2 exercice2.7
Role: affiche le plus petit nombre premier directement supérieur ou égal à l'entier saisi
*/

#include<iostream>
#include<cmath>

using namespace std;

// fonction pour déterminer si un nombre est premier ou non

bool estpremier(int n)
{
	int i;
	if (n<=1) { // tout entier strictement inférieur a 2 n'est pas premier
		return(false);
	}
	else {
		for (i=2; i<=sqrt(n); i++) { // On commence à 2 car 1 n'est pas premier
			if (n%i==0){ // n n'est pas premier si il est divisible par un entier autre que 1 et lui-même
				return(false); 
			}
		}
	}
	return(true);	
}

// algorithme qui donne le plus petit nombre premier directement supérieur ou égal à l'entier saisi

int main()
{ 
	int x,a;

	cout<<"Saisir un entier"<<endl;
	cin>>x;
	a=x;

	if (estpremier(x)) {
		cout<<x<<" est un nombre premier."<<endl;
	}
	else {
		
		while ( ! estpremier(x)){
			x=x+1; 
		}
	cout<<"le plus petit nombre premier directement superieur a "<<a<<" est "<<x<<endl;
	}
}

/* Jeux de Tests: 

input "7" : output "7" (test de 7 car positif et premier)
input "8" : output "11" (test de 8 car positif et non premier)
input "0" : output "2"  (test de 0 car non premier et limite entre positif et négatif)
input "-15" : output "2" ( test de -15 car négatif)
input "1" : output "2" ( test de 1 car non premier)
input "1375" : output "1381" (test de 1375 car positif et non premier(divisible par 5)) 
input "1381" : output "1381" ( test de 1381 car c'est le plus petit nombre premier au-dessus de 1375)

Les tests ont tous bien fonctionnés et nous avons obtenu les résultats attendus. 
*/

