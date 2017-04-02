Exercice 1:

//Calcul d'âge;
n = Saisie('annee de naissance');
m = 2000 - n;
f = 2020 - n;
Ecrire('votre age est ' + m + ' en 2000');
Ecrire('votre age est ' + f + ' en 2020');

//Calcul d'age pour le 31aout 2000
a = Saisie('mois de naissance');
b = Saisie('annee de naissance');
c = Saisie('jour de naissance');
if (a <= 8) 
  d = (2000 - b) - 1;
else
  d = 2000 - b;
Ecrire('votre age est ' + d + ' le 31 aout 2000');
if (c <= 15) 
  if (a <= 8) 
    d = (2000 - b) - 1;
  else
    d=2000-b;
else 
  if (a<8)
  d=(2000-b)-1;
  else
    d=(2000-b);
Ecrire('Votre age est '+d+' le 15aout 2000');

Exercice 2:

//nombre de jours dans le mois
Ecrire('annee');
ecrire('mois').
bis=('annee'%400);
if (mois%2)
  res=31-Math.floor(mois/9);
else
  res=30+Math.floor(mois/8);
if (mois==2)
if (bissextile)
  res=29;
else
  res=28;
Ecrire('le nombre de jours dans le mois est '+res);