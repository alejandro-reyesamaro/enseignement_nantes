//Programme : Calculer Age


/*var date, mois, jour, age2020, age2000, ageR2000, ageRC2000;

date = Saisie('Saisissez votre année de naissance');
mois = Saisie('Saisissez votre mois de naissance');
jour = Saisie('Saisissez votre jour de naissance');

age2020 = 2020 - date;
age2000 = 2000 - date;
ageR2000 = 2000 - date;
if(mois > 8)
{
  ageR2000 -= 1;
}
ageRC2000 = 2000 - date;
if(mois == 8 && jour > 15 || mois > 8)
{
  ageRC2000 -= 1;
}
Ecrire('Vous aurez ' + age2020 + ' au 31 décembre 2020.');
Ecrire('Vous aurez ' + age2000 + ' au 31 décembre 2000.');
Ecrire('Vous aurez ' + ageR2000 + ' au 31 aout 2000.');
Ecrire('Vous aurez ' + ageRC2000 + ' au 15 aout 2000.');*/

//Programme : Nombre jour dans le mois

/*var mois, annee, res, bis;

mois = Saisie('Saisissez un mois');
annee = Saisie('Saisissez une année');
bis = (annee%4 == 0 && annee%100 != 0) || annee%400 == 0;
if(mois%2 != 0)
{
  res = 31 - Math.floor(mois/9);
}
else
{
  res = 30 + Math.floor(mois/8);
}
if(mois == 2)
{
  if(bis)
  {
    res = 29;
  }
  else
  {
    res = 28;
  }
}

Ecrire(res);*/



//Programme : Tortue Logo
/*var n, angle;

n = Saisie('Saisissez n');
angle = 360/n;

for(var i = 0; i<n; i++)
{
  Avancer(50);
  Droite(angle);
}*/

//Programme : Verlan

/*var motSaisi, motFinal, lettre, length;

lettre = '';
motSaisi = '';
motFinal = '';

while(lettre != '.')
{
  lettre = Saisie('Saisissez une lettre');
  if(lettre != '.')
  {
    motSaisi += lettre;
  }
}
length = motSaisi.length;
for(var i = length-1; i >= 0; i--)
{
  motFinal += motSaisi[i];
}

Ecrire(motFinal);*/
