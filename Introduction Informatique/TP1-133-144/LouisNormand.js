// TP n°2

/*
//------Exercice 1
//Variable
var age,anee,mois,jour;
//Début
jour=Saisie('Jour de naissance');
mois=Saisie('Mois de naissance');
annee=Saisie('Année de naissance');


age=2020-annee;
Ecrire('Vous aurez '+age+' ans au 31 décembre 2020.');

if(annee<=2000)	{
  age=2000-annee;
  Ecrire('Vous aviez '+age+' ans au 31 décembre 2000.');

  if(mois<=9)	{
    Ecrire('Vous aviez '+age+' ans au 31 août 2000.');
    
    if(jour>15 && mois==9)	{
      age--;
      if(age<0)	{
        Ecrire("Vous n'êtiez pas né au 15 août 2000");
      } else {
      Ecrire('Vous aviez '+age+' ans au 15 août 2000');
      }
    } else {
      Ecrire('Vous aviez '+age+' ans au 15 août 2000'); 
    }
    
  } else {
    age--;

    if(age<0)	{
      Ecrire("Vous n'êtiez pas né au 31 août 2000");
    } else {
    Ecrire('Vous aviez '+age+' ans au 31 août 2000.');
    Ecrire('Vous aviez '+age+' ans au 15 août 2000');
    }
  }
} else {
 Ecrire("Vous n'êtiez pas né en 2000"); 
}
//Fin
*/

/*
//------Exercice 2
//Variable
var mois,annee;
//Début
mois=Saisie("Le mois");
annee=Saisie("L'annee");

if (mois!=2)	{
 if(mois==4 || mois==6 || mois==9 || mois==11)	{
   Ecrire('Il y a 30 jours dans votre mois');
 } else {
   Ecrire('Il y a 31 jours dans votre mois');
 }
} else {
 if((annee%4==0 && annee%100!=0) || (annee%400==0))	{
   Ecrire('Il y a 29 jours dans votre mois');
 } else {
   Ecrire('Il y a 28 jours dans votre mois');  
 }
}
//Fin
*/

/*
//------Exercice 3
//Variable
var n,i;
//Début
n=Saisie('Nombre de  côtés');

for(i=1;i<(n+1);i++)	{
 Avancer(20);
 Droite(360/n);
}
//Fin
*/


/*
//-------Exercice 4

var mot,n;
//Début
n=Longueur(mot);
//Fin
*/
