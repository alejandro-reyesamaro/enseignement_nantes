//KURTALIQI Endrit GAUCHER Marc E165770K

//Programme Calcul age

//variables
var annee,an,j,m; //entier

//Début

//Saisies
j=Saisie('jour de naissance');
m=Saisie('mois de naissance');
annee=Saisie('annee de naissance');

//Calcul de l'age au 31 décembre 2020
an=2020-annee;
Ecrire('En 2020 vous aurez '+ an + 'ans');

//Calcul de l'age au 31 décembre 2000
if(annee<=2000){
  an=2000-annee;
  Ecrire('Vous avez eu  '+ an+ 'ans en 2000');

//calcul de l'age au 31 aout 2000
if(m<=9){
  Ecrire('Vous avez eu '+ an+ 'ans au 31 aout 2000');
  }else{
  an=an-1;
  Ecrire('Vous avez eu '+ an+ 'ans au 31 aout 2000');
}

//calcul de l'age au 15 aout 2000
if(m<=9 && j<=15){
  Ecrire('Vous avez eu '+ an+ 'ans au 15 aout 2000');
}else{
  Ecrire(an=an-1);
  Ecrire('Vous avez eu '+ an+ 'ans au 15 aout 2000');
}
  

}else{
  Ecrire('Vous n etiez pas ne');
}
//Fin algo

// Test réalisé
//annee=1998  mois=01 jour=01 : 2020->22ans  2000->2ans 31 aout 2000->2ans 15 aout 2000→2ans
