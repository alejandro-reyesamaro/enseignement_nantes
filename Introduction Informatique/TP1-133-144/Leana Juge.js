Léana Jugé
// Calculs âges
//Variables
var annee, mois, jour, age;
//Début algorithme
annee = Saisie('Saisissez votre année de naissance');
mois = Saisie('Saisissez votre mois de naissance en chiffres.');
jour = Saisie('Saisissez votre jour de naissance.');
age = 2020 - annee;
Ecrire('Le 31 décembre 2020 vous aurez ' + age + ' ans.');
age = 2000 - annee;
if (age < 0) {
  Ecrire('En 2000 vous n-étiez pas né.');
} else {
  Ecrire('Le 31 décembre 2000 vous aviez ' + age + ' ans.');
  if (mois <= 8) {
    Ecrire('Le 31 août 2000 vous aviez ' + age + ' ans.');
    if (jour <= 15) {
    Ecrire('Le 15 août 2000 vous aviez '+age+' ans.');
  } else {
    Ecrire('Le 15 août 2000 vous n-étiez pas né.');
  }
 
   }
  }
//Fin algorithme
