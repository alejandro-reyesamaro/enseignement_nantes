// Université de Nantes - X2I0010 Algorithmique et programmation 2
// HERAUD Killian - TP:Decalage Circulaire Exercice 3.6

#include<iostream>
using namespace std;

//-----Tableau-----
const int N=10;

typedef struct {
	int nbc;
	int Contenu[N];
} T_tabEnt;


//-----Fonction Tableau_vide-----
bool tableau_Vide(T_tabEnt TT) {
	return TT.nbc==0;
}


//-----Procédure affiche_Tableau-----
void affiche_Tableau(T_tabEnt TT){
	int j;
	for (j=0; j<= TT.nbc-1; j++){
		cout<< TT.Contenu[j] << " | ";
	}
	cout<<endl;
}


//-----Procedure Saisie_Tableau-----
void saisie_Tableau(T_tabEnt & TT) {
	char reponse= 'Y';
	while(reponse == 'Y') {
		cout<< "Rentrer la valeur de la case "<< TT.nbc <<" : ";
		cin>> TT.Contenu[TT.nbc];
		cout<< "Voulez vous continuer la saisie dans le tableau? (Y/N): ";
		cin>> reponse;
		TT.nbc ++;
	}
}


//-----Procédure Decalage_De_Un-----
void Decalage_De_Un(T_tabEnt & TT) {
	int delta;
	int stock;
	stock = TT.Contenu[TT.nbc-1];
	for (delta = 1; delta < TT.nbc; delta++) {
		TT.Contenu[TT.nbc-delta] = TT.Contenu[TT.nbc-delta-1];
	}
	TT.Contenu[0] = stock;
}


//-----Procédure Decalage Recursive-----
void Decalage_R(T_tabEnt & TT, int decal) {
	if (decal >= 1) {
		Decalage_De_Un(TT);
		Decalage_R(TT, decal-1);
	}
}

//-----Procédure Decalage Itérative  //Probleme Fonctionne mal.
void Decalage_I(T_tabEnt & TT, int decal) {
	T_tabEnt tempo;
	int indice;
	for (indice = 0; indice < TT.nbc; indice++) {
		tempo.Contenu[indice] = TT.Contenu[indice];
	}
	for (indice = 0; indice < TT.nbc; indice++) {
		TT.Contenu[(indice-decal)%TT.nbc] = tempo.Contenu[indice];
	}
}


//-----Programme Principal-----
int main() {
	T_tabEnt TT;
	TT.nbc = 0;
	int methode;
	int decal;
	saisie_Tableau(TT);
	affiche_Tableau(TT);
	cout<< "Quelle méthode voulez vous utilisez?" << endl;
	cout<< " 1 : itérative" <<endl;
	cout<< " 2 : récursive" <<endl;
	cout<< "Votre méthode : ";
	cin>> methode;
	cout<< "De combien voulez vous faire votre décalage? : ";
	cin>> decal;
	if (methode == 2) {
		cout<< "Utilisation méthode récursive." <<endl;
		Decalage_R(TT, decal);
	} else if (methode == 1) { //Probleme Fonctionne mal.
		cout<< "Utilisation méthode itérative." <<endl;
		Decalage_I(TT, decal);
	}
	affiche_Tableau(TT);
}
