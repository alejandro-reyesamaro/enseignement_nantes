//COCHET Klervi BENOIST Bettina

//TP 2

//Algo exercice 1 : Age de la personne selon sa date de naissance
var a, m, j, age1, age2, age3, age4;
a = Saisie('ann�e de naissance');
m = Saisie('mois de naissance');
j = Saisie('jour de naissance');
age1 = 2020 - a;
age2 = 2000 - a;
if (m <= 8) //si la personne est n�e en aout ou avant
{
  age3 = 2000 - a;
}
else //Si la personne est n�e apr�s aout
  age3 = 2000 - (a + 1);
if (m < 8 || (m == 8 && j < 15)) //si la personne est n�e avant le 15 aout
{
  age4 = 2000 - a;
}
else //si la personne est n�e apr�s le 15 aout
  age4 = 2000 - (a + 1);
Ecrire('Au 31 d�cembre 2020 votre age est de' + age1);
Ecrire('Au 31 d�cembre 2000 votre age est de' + age2);
Ecrire('Au 31 aout 2000 votre age est de' + age3);
Ecrire('Au 15 aout 2000 votre age est de' + age4);


//Algo exercice 2:  Nombres de jours dans un mois
//Variables
var a, m, j;
//Debut

//Saisie
a = Saisie('ann�e');
m = Saisie('mois');
if (a % 4 == 0) //Si l'ann�e est bissextile
{
  if (m <= 7) //si le mois est juillet ou avant juillet
  {
    if (m % 2 == 0) //Si le mois est pair
      if (m == 2) //SI le mois est f�vrier
      { 
       j=29;}
      else 
    {
     j=30;}
    else //Si le mois est impair
     j=31;
  }
  else //Si le mois est apr�s juillet
    if (m % 2 == 0) //Si le mois est pair
    { 
      j=31;}
    else //Si le mois est impair
      j=30;
}
else //Si l'ann�e n'est pas bissextile
  if (m <= 7)
  {
    if (m % 2 == 0)
      if (m == 2)
      { 
       j=28;}
      else 
    {
     j=30;}
    else
     j=31;
  }
  else
    if (m % 2 == 0)
    { 
      j=31;}
    else
      j=30;
Ecrire( j ); //Affiche le nombre de jours du mois saisie en fonction de l'ann�e saisie

