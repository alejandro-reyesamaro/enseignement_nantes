//SENLIS Oscar RICHET Axel E161888Q

Exercice 1 :
//Calcul âge
//Variable
var jour, mois, annee, age;
//Début
annee = Saisie('Donnez une année de naissance');
mois = Saisie('Donnez un mois de naissance');
jour = Saisie('Donnez un jour de naissance');
age = 2020 - annee;
Ecrire(age);
age = 2000 - annee;
Ecrire(age);

if (mois < 9){
  age = 2000 - annee;
} else {
  age = 1999 - annee;
}
Ecrire(age);

if (mois < 9 && jour < 16){
  age = 2000 - annee;
} else {
  age = 1999 - annee;
}
Ecrire(age);
//FIN
//Test réalisé
/*
07/08/1998 : 22, 2, 2, 2
01/09/1998 : 22, 1, 1, 1
16/08/1998 : 22, 2, 2, 1
*/

Exercice 2 :
//Calcul nombre de jour dans un mois
//Variable
var mois, annee;
//Début
annee = Saisie('Donnez une année');
mois = Saisie('Donnez un mois');
if (mois != 2){
  if (mois == 1 || mois == 3 || mois == 5 || mois == 7 || mois == 8 || mois == 10 || mois == 12) {
    Ecrire('Il y a 31 jours dans le mois');
  } 
  else {
    Ecrire('Il y a 30 jours dans le mois');
  }
}
else {
  if (annee % 4 == 0 && (annee % 100 != 0 || annee % 400 ==0)){
    Ecrire('Il y a 29 jours dans le mois car c\'est une année bissextile');
  } 
  else {
    Ecrire('Il y a 28 jour dans le mois');
  }
}
//FIN


//Test réalisé
/*
02/2008 : 29 jours
02/1998 : 28 jours
04/1995 : 30 jours
01/1995 : 31 jours
*/


Exercice 3 :
//Dessiner polygone à n côtés

//Variable
var n, angle;

//Début
n = Saisie('Saisir un nombre de côté du polygone');
Droite(90);
angle = 360 / n;
for(i = 1; i <= n; i=i+1) {
  Avancer(50);
  Droite(angle);
}
Deplacer(5000,5000);
//FIN
