// Auteur : Talbot Clarisse e163747L Herbreteau Céline e166431D- Universite de Nantes - 2017

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std ;


//création du type vecteur-------------------------------------------------------
struct t_vect {
	int taille;
	int* ptab;
};

//fonction saisie------------------------------------------------------------------
t_vect saisie_vect() {
	int tmp;
	int i;
	t_vect v;

	cout<<"dimension du vecteur"<<endl;
	cin>> v.taille;
	v.ptab = new int [v.taille]; //allocation du tableau stockant les cordonnées
	for ( i=0 ; i<=v.taille-1 ; i++ ) {
		cout<<"valeur"<<endl;
		cin>>tmp;
		v.ptab[i]= tmp;
	}
	return(v);
}


//fonction chargement de données à partir d'un fichier dans un  vecteur--------------------------------
t_vect charg(string nom, int taille) {
	t_vect vect;
	fstream flux;
	int cord;
	int i;
	
	flux.open(nom.c_str(), ios::in); 
	if (flux) {
		vect.taille = taille;
		vect.ptab = new int [vect.taille];
		for ( i=0 ; i<=taille-1 ; i++ ){
			flux>>cord;
			vect.ptab[i]=cord;
		}
		flux.close();
	}else{
		cout<<"impossible"<<endl;
	}
	return(vect);
}
			


//fonction pour calculer le produit scalaire ----------------------------------------------------------
int p_scal(t_vect u1, t_vect u2 ) {
	int i;
	int res;
	res=0;
	if ( u1.taille == u2.taille && u1.taille != 0) {
		for ( i=0 ; i<= u1.taille-1 ; i++ ) {
			res = res + u1.ptab[i] * u2.ptab[i];
		}
		return (res) ;
	}else{
		cout<<"impossible"<<endl;
		return(000);
	}
}

//procédure de désallocation pour deux vecteurs---------------------------------------------------------------
void detruire(t_vect v1,t_vect v2) {
	delete [] v1.ptab;
	delete [] v2.ptab;
}



//algorithime principal ----------------------------------------------------------------------
int main()
{

t_vect v1;
t_vect v2;



v1=saisie_vect();
v2= charg("test", v1.taille );
cout<<"Le produit scalaire est : "<<p_scal(v1,v2)<<endl;
detruire(v1,v2); // désallocation
return(0);
}

/* nous avons un problème de segmentation nous n'avons pas eu le temps de le résoudre*/




