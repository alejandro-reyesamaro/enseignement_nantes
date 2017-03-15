/* Date.cpp - Auteur : Chatellier Pauline   Gr : 243K
Role : Après avoir saisie une date. Affiche si l'année est bisextile,
	le nombre de jours du mois, et la date du lendemain.
*/

#include <iostream>
using namespace std;

//------------------------------------------------------
//Fonction principale

int main () {

//------------------------------------------------------
//Déclaratin des variables

  int jour;
  int mois;
  int annee;
  bool estBissex;
  int nbjmois;
  int jourlend;
  int moislend;
  int anneelend;

//------------------------------------------------------
//Saisie de la date

  cout << "Entrer un numero de jour ";
  cin >> jour;
  cout << "Entrer un numéro de mois ";
  cin >> mois;
  cout << "Entrer un numéro d'année ";
  cin >> annee;

//------------------------------------------------------
//Le booléen prend la valeur vrai si l'année est bisextile, faux dans le cas contraire

  estBissex = false;
  if( ( (annee % 4 == 0) && (annee % 100 != 0) ) || (annee % 400 == 0) ){
    estBissex = true;
  }

//------------------------------------------------------
//Détermination du nombre de jours dans le mois

  if (mois == 2) {        //1er test si le mois est février
    if (!estBissex) {       //février et non bisextile => 28jours
      nbjmois = 28;
    } else {                //février et bisextile => 29jours
      nbjmois = 29;
    }

  } else {                //le mois n'est pas février

    if (mois < 7) {         //le mois fait partie de la première partie de l'année

      if (mois % 2 != 0){     //le mois est impair => 31jours
        nbjmois = 31;
      } else {                //le mois est pair => 30jours
        nbjmois = 30;
      }

    } else {                //le mois fait partie de la seconde partie de l'année

      if (mois % 2 != 0){     //le mois est impair => 30jours
        nbjmois = 30;
      } else {                //le mois est pair => 31jours
        nbjmois = 31;
      }

    }

  }

//------------------------------------------------------
//Détermination de la date du lendemain

  jourlend = jour;         //la date du lendemain prend les valeurs d'aujourd'hui
  moislend = mois;
  anneelend = annee;

  if (jour < nbjmois) {      //le jour n'est pas le dernier jour du mois
    jourlend = jour + 1;       //on passe au jour suivant
  } else {                   //le jour est le dernier jour du mois
    jourlend = 1;              //on passe donc au premier jour du mois suivant
    moislend = mois + 1;
  }

  if (moislend == 13) {      //le mois est passé à décembre + 1 (donc 13)
    moislend = 1;              //on passe donc au 1er janvier de l'année suivante
    anneelend = annee + 1;
  }


//------------------------------------------------------
//Affichage

  if(estBissex){
    cout << "L'année " << annee << " est bissextile, elle comprend 366 jours." << endl;
  } else {
    cout << "L'année " << annee << " n'est pas bissextile, elle comprend 365 jours." << endl;
  }

  cout << "Le mois " << mois << " comprend " << nbjmois << " jours." << endl;

  cout << "Demain nous serons le " << jourlend << "/" << moislend << "/" << anneelend << "." << endl;

}

//------------------------------------------------------
//Jeux d'essai

/*
jour = 1  mois = 1  annee = 1900
résultat : non bissextile, 31 jours, demain : 2/1/1900

jour = 31  mois = 1  annee = 1996
résultat : bissextile, 31 jours, demain : 1/2/1996

jour = 29  mois = 2  annee = 1996
résultat : bissextile, 29 jours, demain : 1/3/1996

jour = 27  mois = 2  annee = 1997
résultat : non bissextile, 28 jours, demain : 28/2/1997

jour = 1  mois = 8  annee = 2000
résultat : bissextile, 31 jours, demain : 2/8/2000

jour = 31  mois = 12  annee = 2000
résultat : bissextile, 31 jours, demain : 1/1/2001
*/

