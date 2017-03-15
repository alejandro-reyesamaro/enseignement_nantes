/* 	MAHIER Loïc     
	groupe 243K
	Exercice N°3.6

Le programme ne rencontre pas d'erreur au lancement, cependant, je n'arrive pas a afficher le tableau */

#include<iostream>
#define N 100

using namespace std;

typedef struct {
	int contenu[N]; 
	int nb; 
} T_tabEnt ;


void decalage1(int decal, T_tabEnt & tab);
void decalage(int decal, T_tabEnt tab);
void affiche_tableau(T_tabEnt tab); 

int main()
{
	int decal;
	char carac;
	T_tabEnt tab;
	tab.nb=0;
	tab.contenu[0]=1;
	tab.contenu[1]=2;
	tab.contenu[2]=3;
	tab.contenu[3]=4;
	tab.contenu[4]=5;
	affiche_tableau(tab);  // on l'affiche une première fois 	
	cout << "De combiens de cases souhaitez vous faire un décalage dans le tableau ?" << endl;
	cin >> decal;
	cout << "Saisissez 'a' pour utiliser la méthode itérative, 'b' pour utiliser la méthode récursive." << endl;
	cin >> carac;
	if(carac=='a'){
		decalage1(decal, tab);
	}
	else if(carac=='b'){
		decalage(decal, tab);
	}
	else{
		cout << "Vous n'avez saisie ni 'a', ni 'b'." << endl;
	}
	affiche_tableau(tab);  // on l'affiche une deuxième fois, ce qui nous permet de voir le décalage.
	return 0;
}


// version itérative

void decalage1(int decal, T_tabEnt & tab){
	T_tabEnt tempo;	
	for(int i=0; i<=(tab.nb-1); i++){  // on recopie le tableau
		tempo.contenu[i]=tab.contenu[i];
	}
	for(int i=0; i<=(tab.nb-1); i++){  // on restitue le tableau avec le décalage
		tab.contenu[(i+decal) % (tab.nb)]=tempo.contenu[i];
	}
}


// version récursive

void decalage(int decal, T_tabEnt tab){
	int stock;	
	stock=tab.contenu[tab.nb-1];  // on met de côté la première valeur du tableau
	for(int i=0; i<=tab.nb-1; i++){
		tab.contenu[tab.nb-i]=tab.contenu[tab.nb-i-1];
	}
	tab.contenu[0]=stock;  // on remet la première valeur dans le tableau
	if(decal<1){
	}
	else 
	{
		decalage(decal-1, tab);
	}
}


// fonction qui va afficher le tableau

void affiche_tableau(T_tabEnt tab){
	for(int i=0; i<tab.nb; i++){
		cout << tab.contenu[i] << endl;
	}
}


