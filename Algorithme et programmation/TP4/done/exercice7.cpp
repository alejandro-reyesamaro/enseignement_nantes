// MOIZEAU Laura
//MERAND Zénaïde
//243K/L
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

//Exercice 5.7 (Vecteurs)
//Question 8 :

using namespace std ;

   struct T_vecteur {
   int taille;
   float *pv; //pointeur vers tableau
} ;

//Fonction produit_scalaire
//Rôle : Retourner le produit scalaire de 2 vecteurs  

   float produit_scalaire(T_vecteur v1, T_vecteur v2){
   int i; 
   float produit;
   int n;
   int m;
   n = v1.taille;//taille du vecteur v1
   m = v2.taille;//taille du vecteur v2


   if ((n = m) && (n != 0) && (m != 0)){
       
      for (i = 0; i <= n-1; ++i) {
            produit = v1.pv[i] * v2.pv[i]; //produit scalaire
      }
   }
   else {
        cout << " Impossible de faire le produit scalaire des 2 vecteurs " << endl;
   } 
  
   return produit;
}

//Question 9 :
// Algorithme principal 
// Rôle : Faire le produit scalaire de 2 vecteurs

   int main() { 
   T_vecteur v1;
   T_vecteur v2;
   v1.pv = new float [2];//Allocation du pointeur
   v2.pv = new float [2];
   
   v1.taille= 2;
   v2.taille = 2;

   v1.pv[0] = 2;
   v1.pv[1] = 7;
   v2.pv[0] = 3;
   v2.pv[1] = 9;
  cout << produit_scalaire(v1, v2) << endl;// Affiche la fonction produit_scalaire
   
   delete []v1.pv;
   delete []v2.pv;


}


//Difficultés rencontrées au niveau du pointeur et de la réalisation de l'algorithme principal pour les valeurs de l'algo
//Nous avons testé l'algorithme, nous arrivons à le compiler.
//La fonction et l'algorithme fonctionnent il donne 63. 
   

