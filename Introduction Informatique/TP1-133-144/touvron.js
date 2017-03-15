// Anatole TOUVRON et Paul LEBER

// Calcul âges confitionnelles

// Déclarations
var j, m, a, w, x, y, z;

//Début
//Saisies

a = SaisieEntier('Veuillez saisir une année');
m = SaisieEntier('Veuillez saisir un mois');
j = SaisieEntier('Veuillez saisir un jour');

//Calculs

w = 2020-a;
x = 2000-a;
y = 2000-a;
if(m>8){
  y= y-1;
}
z=2000-a;
  if(m>=8){
    if(j>15){
      z=z-1;
    }
  }
//Affichages

Ecrire ('age au 31 decembre 2020: ' + w);
Ecrire ('age au 31 decembre 2000: ' + x);
Ecrire ('age au 31 aout 2000: ' + y);
Ecrire ('age au 15 aout 2000: ' + z);

//Fin

// tests réalisés

// Pour date de naissance de 06/05/1998: on a 22 ans, 2 ans, 2 ans et 2 ans
//Pour date de naissance de 04/11/1999: on a 21 ans, 1 an, 0 an et 1 an
//Pour date de naissance de 18/08/1995: on a 25 ans, 5 ans, 5 ans et 4 ans
