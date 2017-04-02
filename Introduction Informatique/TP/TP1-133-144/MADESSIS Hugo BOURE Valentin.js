//MADESSIS Hugo BOURE Valentin

//Algo âge 1

//Variables

var jour , mois , annee ;

//Début

jour=Saisie('Entrer jour de naissance');
mois=Saisie('Mois de naissance');
annee=Saisie('Année de naissance');
annee = 2020-annee;
Ecrire('Vous aurez ' +annee + ' ans le 31 décembre 2020');

//Fin



//Algo âge 2

//Variables

var jour , mois , annee ;

//Début

jour=Saisie('Entrer jour de naissance');
mois=Saisie('Mois de naissance');
annee=Saisie('Année de naissance');
annee = 2000-annee;
Ecrire('Vous aurez ' +annee + ' ans le 31 décembre 2000');

//Fin



//Algo âge 3

//Variables

var jour , mois , annee ;

//Début

jour=Saisie('Entrer jour de naissance');
mois=Saisie('Mois de naissance');
annee=Saisie('Année de naissance');
if(mois<8){
  (annee=2000-annee);
}else{
  (annee= 1999-annee);
}


Ecrire('Vous aurez ' +annee + ' ans le 31 août 2000');

//Fin



//Algo âge 4

//Variables

var jour , mois , annee ;

//Début

jour=Saisie('Entrer jour de naissance');
mois=Saisie('Mois de naissance');
annee=Saisie('Année de naissance');
if(mois<8){
  (annee=2000-annee);
}else{
  if(mois==8){
     if (jour<15){
       annee=2000-annee;
     }else{(annee=1999-annee);}
  }else{
    annee=1999-annee;}
}


Ecrire('Vous aurez ' +annee + ' ans le 15 août 2000');

//Fin




//Algo nombre de jours

//Variables

var annee, mois, jours;

//Debut

annee=Saisie('Entrer année');
mois=Saisie('Entrer mois');

if (mois==1 || mois==3 || mois==5 || mois==7 || mois==8 || mois==10 || mois==12){
      jours=31;
    }else{
      if ((annee % 4==0) && ((annee % 100!=0) || (annee % 400==0))){
        if (mois==2){
          jours=29;
        }else{
        jours=30;}
      }else{
        if (mois==2){
          jours=28;
        }else{
          jours=30;}
      }
    }
Ecrire ('Il y aura ' +jours + ' jours dans le mois de cette année.');

//Fin




