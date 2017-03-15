// groupe 243
// AGASSE Laure E153993J GUIBERT Justine E162787S
//TDTP2 exercice 2.7 Nombres premiers
//rôle: affiche le plus petit nombre premier directement supérieur ou égal à l'entier saisi

#include<iostream>
#include<string>
#include<math.h>

using namespace std;

bool est_premier(int n){ // fonction qui teste si le nombre saisi est premier
	int i;
	
	for(i=2; i<= sqrt(n);++i){// i=2 car 1 divise tous les nombres
		if((n%i)==0){//si n possède un diviseur autre que 1 et lui même
			return false;// ce n'est pas un nombre premier
		} // fin if 
	}// fin for 
	return true;// c'est un nombre premier 
}


int main_agasse(){
	int x;
	cout<<"saisir un entier"<<endl;
	cin>>x;
	while(! est_premier(x)){ // si le nombre n'est pas premier 
		x=x+1; // alors l'entier saisi augmente de 1
}
	cout<<"le nombre premier supérieur ou égal à l'entier saisie est " <<x<<endl;
}

/*
	case 1--> input:"4"
		  output:"5"

	case 2--> input:"1"
		  output:"1"
Le résultat retourné n'est pas un nombre premier. Donc 1 pose problème

	case 3--> input:"17"
		  output:"17"
on teste avec un nombre directement premier

	case 4--> input:"8"
		  output:"11"
on teste avec un entier où le nombre premier supérieur ou égal n'est pas directement le nombre suivant au nombre saisi 
	
	case 5--> input:"etre"
		  output:"0"
Lorsque l'on saisi des lettres ou des caractères autres que des entiers, on obtient 0 ce qui est normal car l'algorithme ne fonctionne qu'avec des entiers 

	case 6--> input:"-15"
		  output:"-15"
Lorsque l'on saisi un nombre négatif, l'algorithme nous renvoie le même nombre donc il ne fonctionne pas pour les nombres négatifs
*/	


//Conclusion: Notre algorithme a bien fonctionné et les résultats obtenus sont ceux que l'on attendait.


