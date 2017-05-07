/* Exercice5.7 - Q.8.9 \ TD-5.cpp - auteur : J. O'NEILL // S. JADEAU
Role : Produit scalaire
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std ;

// Déclaration du type vecteur
struct t_vect {
	int taille;
	float *ptab;
};

// Fonction qui retourne la taille du vecteur (utilisée pour la condition de la fonction produit_scalaire)
int Taille_vect(t_vect vect){
	return vect.taille;
}// Fin fonction

// Fonction qui demande la saisie d'un vecteur
t_vect saisie_vect(t_vect vect){
	int i,nb;
	float val;
	
	cout << "Saisissez le nombre de réels que vous voulez entrer dans ce vecteur : ";
	cin >> nb;
	vect.taille = nb;
	vect.ptab = new float[nb];
	for (i=1; i <=nb ; i++) {
		cout << "Saisissez la valeur de la coordonnée " << i << " du vecteur : ";
		cin >> val;
		vect.ptab[i] = val;
	}//Fin pour
	return vect;
}// Fin fonction

// Fonction qui retourne le produit scalaire de deux vecteurs.
float produit_scalaire(t_vect vect1 , t_vect vect2){
	int i;
	float k;
	int taille;
	k=0;

//Pour que le produit scalaire ait lieu, il faut que les deux vecteurs sooient de même taille et de taile différente de 0.
	if ((vect1.taille == vect2.taille) && (vect1.taille != 0) && (vect2.taille != 0)){ 
		taille = vect1.taille;

		for (i = 0 ; i <= taille-1 ; i++){
			k = vect1.ptab[i] * vect2.ptab[i] + k;
		}
	return k; // k correspond à la valeur du produit scalaire des deux vecteurs
	} else {
			cout << "Les vecteurs saisis ne sont pas de tailles équivalentes. Le produit scalaire retournera alors 0.";
			return 0; //Traitement du cas où les vecteurs ne correspondent pas à la condition.
	} // Fin si
}// Fin fonction

int main () { //Début de l'algorithme
	int i = 0;
	float scal;
	t_vect Vect1 , Vect2;

	Vect2 = saisie_vect(Vect2); //Saisie des coordonnées des premier vecteur
	Vect1 = saisie_vect(Vect1); //Saisie des coordonnées du second vecteur
	scal = produit_scalaire(Vect1,Vect2); //Produit scalaire des deux vecteurs
	cout << "Le produit scalaire donne le résultat suivant : " << scal << endl; //Affichage du résultat du produit scalaire
}

/* Jeux d'essais:
Cas 1:
Vect 1 (1.5,2,3,4)
Vect 2 (1,6)
output : "Les vecteurs saisis ne sont pas de tailles équivalentes. Le produit scalaire retournera alors 0."

Cas 2 :
Vect 1 (1.5,2,3,4)
Vect 2 (1,6,4,5)
output : "Le produit scalaire donne le résultat suivant : 45.5";

On a essayé de produire l'algoriuthme avec des valeurs prélevées dans un fichier mais on a pas réussi à aboutir sur un travail et algorithme qui fonctionne. Par conséquent, nous sommes revenus sur une saisie de base des deux vecteurs. Et l'algorithme fonctionne.
*/





























