// Algorithme: calcul age

// variables

var j,m,annee,age1,age2; //entier

//DEBUT


   j=Saisie('jour de naissance');
   m=Saisie('mois de naissance');
   annee=Saisie('année de naissance');

age1=2020-annee;
Ecrire('le 31 décembre 2020'+'vous allez avoir '+age1+'ans');

if (annee > 2000){
  Ecrire('vous êtes né apres 2000');
}else{
  age1=2000-annee;
  Ecrire('Vous aviez '+age1+' '+'ans au 31 décembre 2000');
      if (m < 9){	//calcul pour savoir si il est née avant le 31 aout 2000
  	     age1=2000-annee;  
           if (j>15 & m==8){
  		     age2=2000-annee-1;
           }else{
      	age2=2000-annee;
    }}else{
      age1=2000-annee-1;   
  }
  }

 
Ecrire('vous aviez '+age2+' ans au 15 aout 2000');  

Ecrire('vous aviez'+' '+age1+' '+'ans au 31 aout 2000');
//fin

Exemples : 
10 janvier 2005→ 15 ans en 2020 et « née après 2000 ».
10 janvier 1998→ 22 ans en 2020, 2 ans au 31 décembre, 31 août, 15 août 2000.
10 octobre 1998→ 22 ans en 2020, 2 ans au 31 décembre 2000, 1 an au 31 et 15 août 2000.
16 août 1998→ 22 ans en 2020, 2 ans au 31 décembre 2000 et au 31 août 2000 et 1 an au 15 août 2000.     
