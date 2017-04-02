/ Algorithme (Calcul de l'âge au 31 Decembre 2000)
// Variables 
var Jour, Mois, Annee , Year, Month, Day;
// Debut
Jour = SaisieEntier('Veuillez saisir votre jour de naissance');
Mois = SaisieEntier('Veuillez saisir votre mois de naissance en chiffre');
Annee = SaisieEntier('Veuillez saisir votre année de naissance');
Year = enChaine(2000-Annee);
Month = enChaine(12-Mois);
Day = enChaine(31-Jour);
Ecrire(Year+'annees'+Month+'mois'+Day+'jours');
// Fin



// Algorithme (Calcul de l'âge au 31 Decembre 2020)
// Variables 
var Annee, Year;
// Debut
Annee = SaisieEntier('Veuillez saisir votre année de naissance');
Year = 2020-Annee;
Ecrire('Vous avez '+Year+' ans.');
// Fin


// Algorithme (Calcul de l'âge au 31 Aout 2000)
// Variables 
var Mois, Annee;
// Debut
Mois = SaisieEntier('Veuillez saisir votre mois de naissance en chiffre');
Annee = SaisieEntier('Veuillez saisir votre année de naissance');
if (Mois<=8) {
Ecrire (2000-Annee+'ans');
  }else{ 
Ecrire (2000-Annee+1+'ans');}
// Fin


// Algorithme (Calcul du nombre de jour dans le mois)
// Variables 
var Mois, Annee;
// Debut
Mois = SaisieEntier('Veuillez saisir votre mois de naissance en chiffre');
Annee = SaisieEntier('Veuillez saisir votre année de naissance');
if (Mois < 8 || (Mois == 8 && Jour < 15) ) {
  Ecrire(2000 - Annee + 'ans');
} 
else 
  Ecrire(2000 - Annee + 1 + 'ans');
// Fin
