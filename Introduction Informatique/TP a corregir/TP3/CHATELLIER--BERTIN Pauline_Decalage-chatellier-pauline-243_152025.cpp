/* Decalage.cpp - Auteur : Chatellier Pauline   Gr : 243K
Role : L'utilisateur saisie un tableau et un nombre le case 
  dont il veut décaler les entiers du tableau.
*/

#include <iostream>
#include <cmath>
using namespace std;

const int N = 30;

typedef struct {
  int contenu[N];
  int nb;
}T_tabEnt;

//---------------------------------------------
//Affichage d'un tableau

void afficheTab (T_tabEnt tab) {

  int i;

  for (i = 0; i < tab.nb; i++) {
    cout << tab.contenu[i];
  }
  //cout << "Le tableau contient " << tab.nb << " cases." << endl;

}

//---------------------------------------------
//Saisie d'un tableau

void saisieTab (T_tabEnt & tab) {

  tab.nb = 0;
  int i;
  int max;

  cout << "Combien de valeur voulez-vous saisir ?";
  cin >> max;

  for (i = 0; i < max; i++) {
    cout << "Entrer les valeurs du tableau une par une" << endl;
    cin >> tab.contenu[i];
    tab.nb = tab.nb + 1;
  }

}

//---------------------------------------------
//Decalage circulaire dans le tableau (itératif)

void decalageIter (int decal, T_tabEnt & tab) {

  T_tabEnt tempo;
  int ind;

  for (ind = 0; ind < tab.nb; ind++) {
    tempo.contenu[ind] = tab.contenu[ind];
  }

  for (ind = 0; ind < tab.nb; ind++) {
    tab.contenu[(ind+decal) % (tab.nb)] = tempo.contenu[ind];
  }

}

//---------------------------------------------
//Decalage circulaire dans le tableau (récursif)

void descalins (T_tabEnt & tab) {

  int stock;
  int ind;

  stock = tab.contenu[tab.nb - 1];
  for (ind = 1; ind < tab.nb; ind++) {
    tab.contenu[tab.nb-ind] = tab.contenu[tab.nb-ind-1];
  }
  tab.contenu[0] = stock;

}

void decalageRec (int decal, T_tabEnt & tab) {

  if (decal < 1) {
  //Rien ne se passe (condition d'arrêt de la récursivité)
  } else {
    descalins(tab);
    decalageRec(decal-1,tab);
  }

}


//---------------------------------------------
//Fonction principal

int main() {

  T_tabEnt tab;
  int dec;


  saisieTab(tab);

  cout << "Votre tableau initial : ";
  afficheTab(tab);
  cout << endl;

  cout << "De combien de case voulez-vous effectuer votre décalage circulaire ?";
  cin >> dec;

  decalageIter(dec,tab);
  cout << "Votre tableau après décalage de " << dec << " case(s) de façon itérative : ";
  afficheTab(tab);
  cout << endl;

  decalageRec(dec,tab);
  cout << "Un nouveau décalage de " << dec << " case(s) de façon récursive : ";
  afficheTab(tab);
  cout << endl;

  return 0;

}
