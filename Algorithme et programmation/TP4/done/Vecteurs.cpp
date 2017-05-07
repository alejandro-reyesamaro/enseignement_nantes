// Leroux Danguy
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std ;

//---------------------------------------------------------------
struct t_vecteur {
	int taille;
	float *ptab;
};

//Fonction saisissant un vecteur

t_vecteur saisie_vecteur()
{
	int nb, i;
	t_vecteur vect;
	float val;
	cout << "Saisir la taille du vecteur." << endl;
	cin >> nb;
	vect.taille=nb;
	vect.ptab= new float [nb];
	for (i = 0; i <= nb-1; ++i) {
		cout << "Saisir les valeurs du vecteur" << endl;
		cin >> val;
		vect.ptab[i]=val;
	}
	return(vect);
}

//5.7.8

float produit_scalaire(t_vecteur V1, t_vecteur V2){
float res;
res=0;
if (V1.taille==V2.taille) {
	for (int i = 0; i <= V1.taille-1; ++i) {
		res=res+((V1.ptab[i]) * (V2.ptab[i]));
	}
	return(res);
}
else {
	cout << " Le produit scalaire n'est pas possible. " <<endl;
	return(res);
}
}

/*/Analyse:

Nous avons testé le programme avec deux vecteurs (1;2;3) et (9;8;7),
l eprogramme nous retourne alors 46.

/*/

//5.7.9

t_vecteur chargement(string nom){
	t_vecteur A;
	fstream flux;
	int i;
	i=0;
	flux.open(nom.c_str(), ios::in);
	if (flux) {
		while (!(flux.eof())){
			flux >> A.ptab[i];
			i=i+1;
		}
		return(A);
	}
	else{
		cout << "Le fichier n'est pas trouvé" << endl;
	}
	flux.close();
}

/*/Analyse:



/*/

int main (){
	string nom;
	t_vecteur A;
	t_vecteur B;
	A=saisie_vecteur();
	cout << "Quel est le nom du fichier?" << endl;
	cin >> nom;
	B=chargement(nom);
	cout << produit_scalaire(A, B) << endl;
}


