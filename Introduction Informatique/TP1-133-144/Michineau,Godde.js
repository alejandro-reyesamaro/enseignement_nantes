// Exercice 1: Calcule âges

//Variables
var  annee , mois , jour, resultat1,resultat2;//entier

//Debut
annee = Saisie('veuillez donner votre annee de naissance');
mois = Saisie('veuillez donner votre mois de naissance');
jour = Saisie('veuillez donner votre jour de naissance');
resultat1 = 2020-annee;
Ecrire('En 2020 vous aurez ' + resultat1 +' ans');
resultat2 = resultat1-20;
Ecrire('En 2000 vous aviez ' + resultat2+ ' ans');
if (mois<8) 
  Ecrire('En aout 2000 vous avez ' + resultat2+' ans');
else 
  Ecrire('En aout 2000 vous avez ' + (resultat2+1)+ ' ans');
   
if (jour<15 && mois<8)
  Ecrire('Le 15 aout 2000 vous avez ' + resultat2 + ' ans');
else
  Ecrire('le 15 aout 2000 vous avez ' + (resultat2+1)+' ans');
//fin

// Exercice 3: polygone

//Variables
var n, i, degre; //entier

//Debut
i = 0;
n = Saisie('nombre de cote');
Deplacer(50,50);
Droite(90);
degre = 360/n;
while (i != n)
{
  Avancer(30);
  Droite(degre);
  i = i + 1;
}
Deplacer(5,5);





//fin

//exercice pas Terminer
// Exercice 6: pierres, feuilles et ciseaux

//Variables
var choix1, choix2 //chaine de caractere

//Debut
choix1 = Saisie('joueur 1 donne ton choix');
choix2=Saisie('joueur 2 donne ton choix');
if (choix1 == pierres && choix2 == ciseaux)
  Ecrire('-1');
else
{
  if(choix1 == feuilles && choix2 == pierres
    Ecrire('-1');
  else
    if(choix1==ciseaux && choix2 == feuilles)
      Ecrire(
 }
//fin
