//exo 1 fiche 2
//calcul d'age

//VARIABLES
var annee, mois, jour, age;
//DEBUT DU PROGRAMME
jour=Saisie('saisir votre jour de naissance');
mois=Saisie('saisir votre mois de naissance');
annee=Saisie('saisir votre annee de naissance');

age=2020-annee;
Ecrire('vous aurez ' + age + ' ans le 31 decembre 2020.');

if (annee <=2000) {
  age=2000-annee;
  
  Ecrire ('vous aviez ' + age + ' ans le 31 décembre 2000.');
} else {
    Ecrire ('vous netiez pas ne.');
  }

if (mois <=9) {
  Ecrire ('vous aviez ' + age + ' ans le 31 aout 2000.');
} else {
  age=age-1;
  Ecrire ('vous aviez ' + age + ' ans le 31 aout 2000.');
}

if (mois==9 && jour<=15) {
  Ecrire ('vous aviez ' + age + ' ans le 15 aout 2000.');
}
//FIN DU PROGRAMME


//exo 2 fiche 2
//jours dans le mois

//VARIBLES
var annee, mois;
//DEBUT DU PROGRAMME
annee=Saisie('saisir lannee voulue');
mois=Saisie('saisir le mois voulu');

if (mois==1 || mois==3 || mois==5 || mois==7 || mois==8 || mois==10 || mois==12) {
  Ecrire ('le mois fait 31 jours.');
} else { 
  if (mois!=2) {
    Ecrire ('le mois fait 30 jours.');
  } else { 
    if (annee%4==0 && annee%100!=0 ) {
      Ecrire ('le mois fait 29 jours.');
    } else { 
      Ecrire ('le mois fait 28 jours.');
    }
  }
}
//FIN DU PROGRAMME


//exo 3 fiche 2
//tortue logo

//VARIABLES
var n, i;
//DEBUT DU PROGRAMME
n=Saisie('saisir le nombre de cotés');
for (i=1; i<n+1; i++) {
  Avancer(100);
  Droite(360/n);
}
//FIN DU PROGRAMME
