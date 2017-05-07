/* Groupe 243 
HERBERT Calvin 	 E16C002B
RAMBAUD Baptiste E165795M
Feuille TP n°5
Feuille TD n°5
Exercice 5.7.9
Rôle : */

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std ;

//Création du type vecteur
struct  t_vect {
	int taille;
	float *ptab;
};

//Fonction permettant la saisie d'un vecteur
t_vect saisie_vect(){
	int nb, i;
	t_vect v;
	cout<<"Taille vecteur: ";
	cin>>nb;
	v.taille = nb;
	v.ptab = new float[nb];
	for (i=0;i<nb;i++){
		cin >> v.ptab[i]; 	
	} 
	return v; 
}	

//Fonction qui charge un vecteur provenant d'un fichier
t_vect charg_vect(string nom){
	int cpt;
	float tmp;
	t_vect v;
	fstream flux;

	cpt = 0;
	flux.open(nom.c_str(), ios::in);
	if (flux){
		while ( !(flux.eof())){
			flux >> tmp;
			cpt++;
		}
	} else {
		cout << "IMPOSSIBLE";
	}
	flux.close();
	v.taille = cpt-1;
	v.ptab = new float[cpt];
	cpt = 0;
	flux.open(nom.c_str(), ios::in);
	if ( flux ){
		flux >> tmp;
		v.ptab[cpt] = tmp;
		while ( !(flux.eof())){
			flux >> tmp;
			cpt++;
			v.ptab[cpt] = tmp;
		}
	} else {
		cout << "IMPOSSIBLE";
	}
	flux.close();
	return v;
}

//Fonction qui désalloue un vecteur
void menage(t_vect v){
	delete[] v.ptab;
}

//Fonction qui fait le produit scalaire de deux vecteurs si possible
float pdt_scal(t_vect v1, t_vect v2){
	int i;
	float tot;
	tot=0;
	if (v1.taille==v2.taille && v1.taille!=0){
		for (i=0;i<v1.taille;i++){
			tot+=v1.ptab[i]*v2.ptab[i];
		}
	}else{
		return NULL ;
	}
	return tot;
}



int main () 
{ 
	string fichier;
	float scal;
	t_vect v1, v2;
	v1=saisie_vect();
	cout << "Nom du fichier contenant le vecteur : ";
	cin >> fichier;
	v2=charg_vect(fichier);
	scal=pdt_scal(v1,v2);
	if(scal==NULL){ //condition si le produit scalaire est impossible
		cout << "Produit scalaire impossible" << endl;
	}else{
		cout << "Le produit scalaire est : " << scal << endl;
	}
	menage(v1);
	menage(v2);
}















