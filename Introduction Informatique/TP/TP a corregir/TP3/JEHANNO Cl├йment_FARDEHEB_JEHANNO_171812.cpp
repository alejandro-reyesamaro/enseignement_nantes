// FARDEHEB, JEHANNO, 249X

//Exercice 3.6

//Version avec procédure

#include <iostream>
#include <cmath>
using namespace std ;

typedef struct { int contenu[10]; int nbc; } T_tab;

/*

//Procédure de décalage
void decalage(int decal, T_tab & tab){

//Variables :
T_tab tempo;
int indice; 

//Début

for(indice=0; indice < tab.nbc; indice++) {		//Copie du tableau
	tempo.contenu[indice] = tab.contenu[indice];
}

for(indice=0; indice < tab.nbc; indice++) {		//Restitution avec décalage
	tab.contenu[(indice + decal)% tab.nbc] = tempo.contenu[indice];
}

}

//Procédure d'affichage
void aff(T_tab Table) {

for (int i=0; i< Table.nbc; i++){
	cout << Table.contenu[i] << " " ;
}

}

int main() {

//Remplissage du tableau
T_tab Table;
Table.contenu[0]=5;
Table.contenu[1]=2;
Table.contenu[2]=65;
Table.contenu[3]=95;
Table.contenu[4]=74;
Table.contenu[5]=8;
Table.contenu[6]=1;
Table.contenu[7]=0;
Table.contenu[8]=46;
Table.contenu[9]=12;
Table.nbc=10;
int x;

cout << endl;
aff(Table);
cout << endl;
cout << "De combien voulez-vous décaler votre tableau ?" << endl;
cin >> x;



decalage(x, Table);

cout << endl;

aff(Table);
}

*/

//Version récursive


//Procédure décalage

void decalage(T_tab & tab) {
int stock, delta;

		stock = tab.contenu[tab.nbc-1];
		for(delta = 1; delta <= tab.nbc-1; delta ++) {
			tab.contenu[tab.nbc-delta] = tab.contenu[tab.nbc-(delta+1)];
		}
		tab.contenu[0] = stock;
	
}

void decalageDE(int decal, T_tab & tab){
	if(decal < 1) {
	}

	else{
		decalage(tab);
		decalageDE(decal-1, tab);
	}
}

//Procédure d'affichage
void aff(T_tab Table) {

	for (int i=0; i< Table.nbc; i++){
	cout << Table.contenu[i] << " " ;
	}
}

int main() {

//Remplissage du tableau
T_tab Table;
Table.contenu[0]=5;
Table.contenu[1]=2;
Table.contenu[2]=65;
Table.contenu[3]=95;
Table.contenu[4]=74;
Table.contenu[5]=8;
Table.contenu[6]=1;
Table.contenu[7]=0;
Table.contenu[8]=46;
Table.contenu[9]=12;
Table.nbc=10;
int x;

cout << endl;
aff(Table);
cout << endl;
cout << "De combien voulez-vous décaler votre tableau ?" << endl;
cin >> x;



decalageDE(x, Table);

cout << endl;

aff(Table);

}
