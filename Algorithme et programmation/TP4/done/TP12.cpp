// 243 - Charpentier Jodie
//TD 3 Exo 5.7


#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std ;

// type enregistrement
struct T_vecteur
  {
   int taille;
   float *pv;
  };

//--------------------------------------------------------------
// fonction produit scalaire
// Role : retourner le produit scalaire de deux vecteurs

float produit_scalaire (T_vecteur v1,T_vecteur v2)
 {
 
  float ps;  
  int i;
 
  int n;
  int m;
  n=v1.taille ;// faire atttention au sens se l'égalité
  m= v2.taille ;
  if ( (n==m) && (n!=0) && (m!=0) )
   {
     for ( i = 0; i<= n-1; ++i )
      {
        ps = v1.pv[i]*v2.pv[i];
      }
   }
  else
   {
     cout << " produit scalaire impossible " << endl;
   }
  return ps;
 }


//Algorithme principal
// Role :

int main ()
 {
   T_vecteur v1;
   T_vecteur v2;
   v1.pv = new float [3];// alloue les cases
   v2.pv = new float [3];
   v1.taille=3;
   v2.taille=3;
  
   //declaration des vecteurs
   v1.pv[0]=5;
   v1.pv[1]=7;
   v1.pv[2]=3;
   v2.pv[0]=6;
   v2.pv[1]=1;
   v2.pv[2]=4;
   cout <<  produit_scalaire (v1,v2) << endl;//appeller la fonction
   delete []v1.pv;//desallouer les cases
   delete []v2.pv;
 }



//test ecrit " produit scalaire impossible " car oubli des déclaration des tailles des vecteurs, maintenant affiche 12













  
 













   
