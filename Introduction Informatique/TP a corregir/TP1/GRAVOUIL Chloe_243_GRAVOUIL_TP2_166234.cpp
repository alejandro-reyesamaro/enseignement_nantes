//Algorithme_Année bissextile : demande à l'utilisateur la saisie de trois entiers (jour, mois, année), renvoie si cette année est bissextile, le nombre de jours dans le mois donné, la date du lendemain de la date donnée; auteur : C.GRAVOUIL


#include <iostream>

using namespace std;

int main()
{
typedef struct date {
int jour;
int mois;
int annee;
};

date ajd; // Structure regroupant le jour, le mois et l'année de la date saisie
date demain; // STructure regroupant le jour, le mois et l'année du lendemain de la date saisie.

int nbjours; //entier ; c'est le nombre de jours du mois saisi
bool bissextile; // booléen, sert à afficher si l'année est bissextile ou non
bool paritemois; //booléen, vrai si le mois a un numéro impair, faux sinon

cout << "Entrez le jour ";
cin >> (ajd.jour);
cout << "Entrez le mois ";
cin >> (ajd.mois);
cout << "Entrez l'année ";
cin >> (ajd.annee);

//On cherche si l'année est bissextile

if ((ajd.annee) % 400 == 0){//Si l'année est divisible par 400, elle n'est pas bissextile;
bissextile= false;
}else{
if ((ajd.annee) % 4 != 0){//Si l'année n'est pas divisible par 4, elle n'est pas bissextile;
bissextile = false;
}else{
if ((ajd.annee) % 100 == 0){// Si l'année est divisible par 4 et par 100, donc divisible par 400, elle n'est pas bissextile.
bissextile = false;
}else{
bissextile = true; //Si l'année est divisible par 4 et pas par 100, elle est bissextile.
}}}

if ((ajd.mois) % 2 ==0){//On teste la parité du mois
paritemois=true;
}else{
paritemois=false;
}

//On calcule le nombre de jours du mois
if ((ajd.mois)==2){// Si le mois saisi est février, on affecte le nombre de jours en fonction du fait que l'année soit ou non bissextile;
if (bissextile==true){
nbjours=29;
}else{
nbjours=28;
}
}else{
if ((ajd.mois)<=7){
if (paritemois==true){//Si le numéro du mois est inférieur ou égal à 7 et pair, alors le mois a 30 jours;
nbjours = 30;
}else{
nbjours=31;//Si le numéro du mois est inférieur ou égal à 7 et impair, alors le mois a 31 jours;
}
}else{
if (paritemois==true){
nbjours=31;//Si le numéro du mois est supérieur à 7 et pair, alors le mois a 31 jours;
}else{
nbjours=30;//Si le numéro du mois est supérieur à 7 et impair, alors le mois a 30 jours;
}}}

if ((ajd.jour)==nbjours){//Dans ce cas, on change de mois le lendemain
if ((ajd.mois)<=11){
(demain.jour)=01;
(demain.mois)=(ajd.mois)+1;
(demain.annee)=(ajd.annee);
}else{//Cas du 31 décembre : on change d'année
(demain.jour)=01;
(demain.mois)=01;
(demain.annee)=(ajd.annee)+1;
}
}else{//Le lendemain appartient au même mois
(demain.jour)=(ajd.jour)+1;
(demain.mois)=(ajd.mois);
(demain.annee)=(ajd.annee);
}

if (bissextile==true){//Affichage
cout << "L'année "<< (ajd.annee) << " est bissextile. "<<endl;
}else{
cout << "L'année "<< (ajd.annee) << " n'est pas bissextile. "<<endl;
}
cout << "Le mois indiqué de cette année a "<< nbjours <<" jours."<<endl;
cout << "Le lendemain sera le "<<(demain.jour)<<"/"<<(demain.mois)<<"/"<<(demain.annee)<<"."<<endl;
}//Fin du code

/*Jeux d'essais :

31/12/2000 : Non Bissextile, le mois a 31 jours, le lendemain est le 01/01/2001.

28/02/2012 : Bissextile, le mois a 29 jours, le lendemain est le 29/02/2012.

24/07/1998 : Non Bissextile, le mois a 31 jours, le lendemain est le 25/07/1998.

19/09/1996 : Bissextile, le mois a 30 jours, le lendemain est le 20/09/1996.

28/02/2011 : Non Bissextile, le mois a 28 jours, le lendemain est le 01/03/2011.

31/07/1995 : Non Bissextile, le mois a 31 jours, le lendemain est le 01/8/1995.

*/
