/* Priscillia GENDRONNEAU et Laura GUILLOTEAU- TDTP5- Exercice 5.7-partie 8 et 9
Role: Calcule le produit scalaire de deux vecteurs (un saisi par l'utilisateur et l'autre donné par l'ordinateur
*/

#include<iostream>
#include<fstream>
#include <string>

using namespace std ;

//Déclaration d'un nouveau type
struct T_vecteur {
	int taille;
	float *ptab;
};


//Fonction qui calcule le produit scalaire de deux vecteurs quand c'est possible 

float produit_scalaire (T_vecteur v1, T_vecteur v2){
	int i;
	float res;	

	res=0;
	if (v1.taille == v2.taille) {
		for (i=0; i<=v1.taille-1; i++) {
			res = res + (v1.ptab[i]*v2.ptab[i]);
		}
		return (res);
	}else{
		return(0);
	}	
}



// Fonction qui permet de remplir les valeurs du vecteur
T_vecteur saisie_vecteur()
{
	int nb, i;
	T_vecteur vect;
	float val;

	cout<<"Saisir la taille du vecteur."<<endl;
	cin>>nb;
	vect.taille=nb;
	vect.ptab=new float[nb];
	
	for(i=0; i<=nb-1; i++) {
		cout<<"Saisir les valeurs du vecteur."<<endl;
		cin>>val;
		vect.ptab[i]=val;
	}
	return(vect);
}

//Fonction Chargement_vecteur

T_vecteur chargement_vecteur (string nom){
	int i, nb;
	float val;
	fstream fic;
	T_vecteur vect;

	nb=0;
	fic.open(nom.c_str(), ios::in);
	if (fic){
		fic>>val;
		while (!(fic.eof())){
			nb=nb+1;
			fic>>val;
		}
	}
	fic.close();
	vect.taille =nb;
	vect.ptab=new float[nb];
	fic.open(nom.c_str(), ios::in);
	for (i=0; i<=nb-1; i++){
		fic>>val;
		vect.ptab[i]=val;			
	}
	fic.close();
	return (vect);
}


//Algorithme principal

int main (){
	
	T_vecteur v1,v2;
	string nom;
	
	v1=saisie_vecteur();
	cout<< "Saisir le nom du fichier ?"<<endl;
	cin>>nom;
	v2=chargement_vecteur(nom);
	cout<<produit_scalaire(v1,v2)<<endl;
}

/*Jeux d'essais
On a eu le temps de tester qu'avec une série de valeurs:
v1: 1;2;3;4
v2: 4;3;2;1
vect=20
*/






