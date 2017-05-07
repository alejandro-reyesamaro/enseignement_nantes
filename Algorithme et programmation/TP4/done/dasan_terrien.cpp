/* algo7_vecteurs.cpp - auteurs : l.Terrien m.Dasan 
Role : manipuler un tableau de reels dont la taille peut etre choisie par l utilisateur en cours d execution 
*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>


using namespace std; 

/* la fonction produit scalaire fonctionne, on l'a testée avec deux vecteurs de meme taille
Par contre il y a un probleme avec la lecture du fichier et le transfert des donnees du fichier dans un vecteur (le terminal affiche le resultat 4.2039e-45)
On a  testé la partie fichier avec un fichier contenant trois réels (1, 2, 3)
*/



//-------------------------------------
// type T_vecteur enregistrement
struct T_vecteur { 
   int taille;
   float* ptab;
};


//-------------------------------------
//fonction qui demande a la fois le nombre de reels que l utilisateur souhaite saisir et leurs valeurs 
T_vecteur saisie_vecteur (){
   int nb, i;
   float val;  
   T_vecteur vect;
   cout << " Veuillez saisir le nombre de reels que vous souhaitez " << endl;
   cin >> nb;
   vect.taille = nb;
   vect.ptab = new float[nb];
   for (i = 1; i <= nb; i++) {
      cout << " Veuillez saisir la valeur des reels" << endl;
      cin >> val ;
      vect.ptab[i-1] = val; 
   }
  return vect ;
}

 
//-------------------------------------
//procedure qui permet de liberer l espace memoire occupe par le vecteur passe en parametre 
void desallocation( T_vecteur vect) {
  delete[]vect.ptab;
}


//-------------------------------------
//fonction qui permet de calculer le produit scalaire de deux vecteurs 
float produit_scalaire( T_vecteur vect_a, T_vecteur vect_b ) {
  int i; 
  float scal; 
  if (vect_a.taille == vect_b.taille && vect_a.taille!=0 && vect_b.taille!=0) {
  scal = 0; 
    for (i = 1; i <= vect_a.taille; i++) {
      scal = vect_a.ptab[i-1] * vect_b.ptab[i-1] + scal; 
    } 
   return scal; 
  }
}



//-------------------------------------
// procedure qui permet de prendre en parametre un vecteur et l affiche sur la sortie standard
void affiche_vecteur(T_vecteur vect) {
int i;
  for (i = 1; i <= vect.taille; i++) {
  cout << vect.ptab[i-1] << endl; 
  }
}



//-------------------------------------
// fonction de transfert de reels d'un fichier vers un vecteur
T_vecteur transfert_fic (int nb, string fic) {

fstream flux;
T_vecteur vect;
int i;

   vect.taille = nb;
   vect.ptab = new float[nb];

flux.open(fic.c_str(), ios::in);  
  if (flux) 
       {
          for (i = 1; i <= vect.taille; i++) {
              flux >> vect.ptab[i-1];
		}
  }

  flux.close();

return vect;
}  
   


//-------------------------------------
// fonction principale

int main()
{ 
   
T_vecteur vect1, vect2;
fstream flux; 
string fichier_vect;
int i;
float val;


// ouverture du fichier en lecture et on compte le nombre de valeurs
  i = 0;
  flux.open(fichier_vect.c_str(), ios::in);   
  if (flux) 
    {
     flux >> val;
       while (!(flux.eof())) 
      {
     i = i+1;
     flux >> val;
      }
   flux.close();
    }


// transfert des donnees du fichier dans un T_vecteur
vect1 = transfert_fic (i, fichier_vect);

// saisie du deuxieme vecteur par l'utilisateur
vect2 = saisie_vecteur ();

// calcul et affichage du produit scalaire
cout << "produit scalaire = " << endl;
cout << produit_scalaire (vect1, vect2) << endl;

// desallocation tableaux vecteurs
desallocation (vect1);
desallocation (vect2);

 
   return (0);
}
 
