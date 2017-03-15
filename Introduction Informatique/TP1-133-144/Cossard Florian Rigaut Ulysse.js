// Cossard Florian, Rigaut Ulysse 168920J

// Algorithme : Calcule ages
// Variables
var jour, mois, annee;
var age;

// Debut
jour = SaisieEntier('Entrer votre jour de naissance :');
mois = SaisieEntier('Entrer votre mois de naissance :');
annee = SaisieEntier('Entrer votre année de naissance :');

age = 2020 - annee;
if(age < 0)
  age = 0;
Ecrire('Le 31 décembre 2020, vous aurez ' + age + ' ans.');

age = 2000 - annee;
if(age < 0)
  age = 0;
Ecrire('Le 31 décembre 2000, vous aurez ' + age + ' ans.');

if((mois > 8) && (age > 0))
  age = age - 1;
Ecrire('Le 31 août 2000, vous aurez ' + age + ' ans.');

if((mois == 8) && (jour > 15) && (age > 0))
  age = age - 1;
Ecrire('Le 15 août 2000, vous aurez ' + age + ' ans.');
// Fin

// Ensemble de jeux d'essai
//
// jour, mois, annee => age
// Pour 31 decembre 2020 :
//   1, 1, 2000 => 20 ans, FONCTIONNE
// Pour 31 decembre 2000 :
//   1, 1, 1990 => 10 ans : FONCTIONNE
// Pour 31 aout 2000 :
//   1, 8, 1990 => 10 ans : FONCTIONNE
// Pour 15 aout 2000 :
//   17, 8, 1990 => 9 ans : FONCTIONNE

