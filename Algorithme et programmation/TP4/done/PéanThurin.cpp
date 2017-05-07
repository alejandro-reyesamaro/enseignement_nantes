// Auteur : PEAN Marie THURIN Gauthier 

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std ;

struct T_vecteur{
	int taille;
	int *ptr;
};

float produit_scalaire(T_vecteur vect_1,T_vecteur vect_2){
	float p_scal;
	int i;
	
	if((vect_1.taille==vect_2.taille)&&(vect_1.taille!=0)){
	p_scal=0;
	for(i=0; i<=vect_1.taille;i++){
		p_scal=(vect_1.ptr[i])*(vect_2.ptr[i])+p_scal;
		}
		cout<<"Le produit scalaire des vecteurs 1 et 2 est: ";
	return p_scal;
	}
	cout<<"Le produit scalaire ne peut pas être effectué";
	return 0;
}

int main(){
	T_vecteur vect_1,vect_2;
	int i,nb;
	//On saisit les valeurs du vecteur 1
	cout<< "Saisir la taille du premier vecteur :";
	cin>>vect_1.taille;
	vect_1.ptr = new int[vect_1.taille];
	for(i=0;i<vect_1.taille;i++){
		cout<< "Saisir la valeur "<<i+1<<" du premier vecteur: ";
		cin>> vect_1.ptr[i];
	}
	
	//On saist les valeurs du vecteur 2 à partir d'un fichier
	fstream flux;
	int taille_flux,j;
	char nom;
	float val;
	j=0;
	cout<< "Saisir le nom du fichier contenant le vecteur: ";
	cin>>nom;
	taille_flux=0;
	flux.open(nom.c_str(),ios::in);
	if(flux){
		while(!flux.eof()){
			flux>>val;
			taille_flux++;
		}
		vect_2.taille=taille_flux;
	}else{
		cout<<"Le fichier n'existe pas"<<endl;
	}
	flux.close();
	vect_2.ptr = new int[vect_2.taille];
	flux.open(nom.c_str(),ios::in);
	if(flux){
		while(!flux.eof()){
			flux>>val;
			vect_2.ptr[j]=val;
			j++;
		}
	}
	flux.close();
	
	cout<< produit_scalaire(vect_1,vect_2)<<endl;
	
}
