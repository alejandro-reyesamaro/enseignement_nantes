// Cossard Florian Rigaut Ulysse 168920J

// Algorithme : Nombre de jours dans un mois
// Variables
var mois, annee;
var jours;

// Début
mois = SaisieEntier('Entrer le mois :');
annee = SaisieEntier('Entrer l\'année :');

if(mois == 2)
{
  if(((annee % 4 == 0) && (annee % 100 != 0)) || (annee % 400 == 0))
    jours = 29;
  else
    jours = 28;
}
else if(((mois <= 7) && (mois % 2 == 1)) || ((mois > 7) && (mois % 2 == 0)))
  jours = 31;
else
  jours = 30;

Ecrire('Il y a ' + jours + ' jours dans le mois.');
// Fin

// Ensemble jeux d'essai :
// mois, annee => nombre de jours
// 2, 2000 => 29 FONCTIONNE
// 7, 2040 => 31 FONCTIONNE

