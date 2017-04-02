//Ecriture de procédures qui prennent en paramètre un entier decal positif et un tableau d'entiers et effectuent un décalage circulaire de decal cases à droite dans le tableau d'entiers. Auteur : C. Gravouil

#include <iostream>
#include <cmath>
using namespace std;
const int N=100;


typedef struct T_tabEnt { 
int contenu[N]; 
int nb;
 }; 

//-------------------------------------------------------------------------------

//Version itérative

void decalage (int decal, T_tabEnt & thetableau){
T_tabEnt tempo;
int indice;
	for(indice=0; indice <= (thetableau.nb)-1 ; indice=indice+1){
	tempo.contenu[indice]=thetableau.contenu[indice];
	};
	for(indice=0; indice <= (thetableau.nb)-1 ; indice=indice+1){
	thetableau.contenu[(indice+decal)%(thetableau.nb)]=tempo.contenu[indice];
	};
}

//---------------------------------------------------------------------------------
	//Version récursive

		void descalins (T_tabEnt & thetableau){//Effectue le décalage pour decal=1
		int thevaleur;
		int delta;

		thevaleur= thetableau.contenu[thetableau.nb-1];
		for (delta=1; delta <= (thetableau.nb)-1; delta=delta+1){

			thetableau.contenu[thetableau.nb-delta]=thetableau.contenu[thetableau.nb-delta-1];
		};

		thetableau.contenu[0]=thevaleur;
		}
		//------------------------------------------------

		void decalagerecursif (int decal, T_tabEnt & thetableau){
		if (decal >= 1){
			descalins(thetableau);
			decalage(decal-1, thetableau);
		}
		}		

//---------------------------------------------------------------------------------
void saisie_tableau(T_tabEnt &table){ //Permet la saisie du tableau pour l'algorithme principal
bool continuer;
bool validitereponse;
string reponse;

continuer=true;
table.nb=0;
validitereponse=false;

while(continuer==true && table.nb<N){
cout << "Saisir l'entier suivant" <<endl;
cin >> table.contenu[table.nb];
(table.nb)=(table.nb)+1;
cout << "Voulez-vous stopper la saisie ?"<<endl;
cin >> reponse;
	while(validitereponse==false){ //Vérifie que la réponse saisie est lue et valide
			if (reponse=="Non" || reponse == "non"){
			validitereponse=true;
			}else{
				if (reponse=="Oui" || reponse == "oui"){

					validitereponse=true;
					continuer=false;
				}else{
				cout << "Votre réponse n'est pas valide, merci de recommencer."<<endl;
				cout << "Voulez-vous stopper ?"<<endl;
				cin >> reponse;
				}
			}
		}
		validitereponse=false;
}
if (table.nb == N){
cout << "Vous avez atteint la limite de taille du tableau"<<endl;
}
}
//------------------------------------------------------------
void affiche_tableau (T_tabEnt table){
	int ent;
	for (ent=0; ent<=table.nb-1; ent=ent+1){
		cout << table.contenu[ent] << endl;
	}
}
//------------------------------------------------------------

int main(){
T_tabEnt untableau;
T_tabEnt lememetableau; //On va recopier le tableau "untableau" dans ce tableau et appliquer à chacun une version différente (itérative ou récursive), cela permettra de comparer les résultats.
int decal;
int indice; //Compteur

saisie_tableau(untableau);

for (indice=0; indice<= (untableau.nb)-1 ; indice=indice+1){
	lememetableau.contenu[indice]= untableau.contenu[indice];
};
lememetableau.nb=(untableau.nb);

cout << "Quel est le décalage ?"<<endl;
cin >> decal;
decalage (decal, untableau);
decalagerecursif (decal, lememetableau);

cout << "Voici le résultat avec la procédure itérative" <<endl;
affiche_tableau(untableau);
cout << "Voici le résultat avec la procédure récursive" <<endl;
affiche_tableau(lememetableau);
}

//Jeux d'essais : J'ai saisi les valeurs 1, 2, 3 ,4, 5, 6 avec des valeurs de décalage de 0 à 4 et de 12
