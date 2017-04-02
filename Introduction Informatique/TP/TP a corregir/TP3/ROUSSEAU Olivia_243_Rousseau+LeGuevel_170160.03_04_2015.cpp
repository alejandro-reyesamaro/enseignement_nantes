/* 243_Rousseau+LeGuevel.03_04_2015.cpp -auteurs: O.Rousseau et A.Le Guevel
Role : Manipulation d'un tableau
*/

#include<iostream>

using namespace std;

const int N = 5;

typedef int T_tab_int[N];
typedef struct {
	int contenu[N] ;
	int nb ;
} T_tabEnt ;

// Procédure itérative
void decalage(int decal,T_tabEnt & tab) {
	//Variables
	T_tabEnt tempo;
	int ind;
 for(ind=0;ind <= tab.nb-1; ++ind) {
 	tempo.contenu[ind]=tab.contenu[ind];
 }
 for(ind=0;ind<=tab.nb-1;++ind) {
 	tab.contenu[(ind+decal)%tab.nb]=tempo.contenu[ind];
 }
}


//Procédure pour décaler une seule fois
void decal1(T_tabEnt & tab ) {
	//Variables
	int stock;
	int ind;
 stock=tab.contenu[tab.nb-1];
	for (ind=1;ind<=tab.nb-1;++ind) {
 		tab.contenu[ind-1]=tab.contenu[ind];
	}
 tab.contenu[0]=stock;
}

//Procédure récursive qui utilise decal1
void decal(int deca, T_tabEnt & tab ) {
 if (deca>=1) {
 	decal1(tab);
 	decal(deca-1,tab);
 }
}


//Procédure pour afficher un tableau
void affiche_tableau (T_tabEnt tab) {
  // Variables 
  int ind ;
  //
  for (ind = 0 ; ind < N ; ++ind) {
	cout << tab.contenu[ind] << " " ;
  }
  cout << endl ;
}





  


//Test des procédures avec jeux d'essais

int main() {
 //Variable
 T_tab_int hello = {1,2,3,4,5};
 T_tabEnt tabf ;
 int ind;
 int indice;
 int i;
    //Initialisation de l'enregistrement
  tabf.nb=N;
  for(ind=0;ind<N;++ind){
	tabf.contenu[ind]=hello[ind];
  }
//Tests de la procédure itérative
 cout <<"Voici votre tableau initial: ";
 for (indice = 0 ; indice < N ; ++indice) {
	cout << hello[indice] << " " ;
 }
  cout << endl ;
 cout << endl;
 cout<<"Tests de la procédure itérative"<<endl;

cout<< "On effectue un décalage de 1 " << endl;
  decalage(1,tabf);
  affiche_tableau(tabf);

  tabf.nb=N;
  for(ind=0;ind<N;++ind){
	tabf.contenu[ind]=hello[ind];
  }
cout<< "On effectue un décalage de 2 "<< endl;
  decalage(2,tabf);
  affiche_tableau(tabf);

  tabf.nb=N;
  for(ind=0;ind<N;++ind){
	tabf.contenu[ind]=hello[ind];
  }
cout<< "On effectue un décalage de 3 " << endl;
  decalage(3,tabf);
  affiche_tableau(tabf);

  tabf.nb=N;
  for(ind=0;ind<N;++ind){
	tabf.contenu[ind]=hello[ind];
  }
cout<< "On effectue un décalage de 4 " << endl;
  decalage(4,tabf);
  affiche_tableau(tabf);

  tabf.nb=N;
  for(ind=0;ind<N;++ind){
	tabf.contenu[ind]=hello[ind];
  }

//Tests de la procédure récursive
  cout << endl;
  cout<<"Tests de la procédure récursive"<<endl;

cout<< "On effectue un décalage de 2 " << endl;
  decal(2,tabf);
  affiche_tableau(tabf);
  return (0) ;
}










