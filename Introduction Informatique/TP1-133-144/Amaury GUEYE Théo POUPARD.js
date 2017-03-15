Amaury GUEYE Théo POUPARD 133B

// Algorithme: Calcul âges
// Déclarations
var jour, mois, annee, age; //entiers

// Début
jour=SaisieEntier('Saisir jour de naissance');
mois=SaisieEntier('Saisir mois de naissance');
annee=SaisieEntier('Saisir année de naissance');


// Age au 31 décembre 2020
if (annee<2020)
{
  age=2020-annee;
}
else
{
  age=0;
}
Ecrire ('En 2020, la personne aura ' + age + ' ans');


// Age au 31 décembre 2000
if(annee<2000)
{
  age=2000-annee;
}
else{
  age=0;
}
Ecrire ('En 2000, la personne avait ' + age + ' ans');


// Age au 31 août 2000
if (mois<=8)
{
  age=2000-annee;
}
else
{
  age=2000-annee-1;
}
Ecrire ('Au 31 Août 2000, la personne avait ' + age + ' ans');



// Age au 15 août 2000
if (mois<=8)
{
  if (jour<=15)
  {
  age=2000-annee;
  }
else
{
  age=2000-annee-1;
}}
Ecrire ('Au 15 Août 2000, la personne avait ' + age + ' ans');

//Fin








// Algorithme: Nombre de jours dans le mois
// Déclarations
var mois, annee, jours, bisextile; //entiers

// Début
mois=SaisieEntier('Saisir mois');
annee=SaisieEntier('Saisir annee');

if (annee%4==0 )
{
 if(annee%100==0)
 {
   if(annee%400==0)
   {
     bisextile=1;
   }
 else
 {
   bisextile=0;
 }}
else
{
  bisextile=1;
}}
else
{
  bisextile=0;
}


//Janvier
if (mois==1)
 {
   jours=31;
 }

//Février
if (mois==2)
{
  jours=28+bisextile;
}

//De Mars à Juin
if (mois>2 && mois<8)
{
  if(mois %2==0)
  {
    jours=30;
  }
  else
  {
    jours=31;
  }}

// D'Août à Décembre
if (mois>7 && mois<13)
{
  if (mois%2==0)
  {
    jours=31;
  }
  else
  {
    jours=30;
  }
}

Ecrire('Il y a ' + jours +' jours dans ce mois.');





// Algorithme: Tortue logo
// Déclaration
var n; // entiers

// Début
n=SaisieEntier('Saisir le nombre de côtés n');


while(n<3)
{
  n=SaisieEntier('Saisir le nombre de côtés n supérieur à 2.');
}

