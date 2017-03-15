// Calcul d'age
var age,jour,mois,annee;

jour=SaisieEntier();
mois=SaisieEntier();
annee=SaisieEntier();

age=2020-annee;		//Age au 31 decembre 2020
Ecrire('Age au 31 décembre 2020 =' +age);

age=2000-annee;		//Age au 31 decembre 2000
if (annee>=2000)
  age=0;
Ecrire('Age au 31 décembre 2000 =' +age);

age=2000-annee;		//Age au 31 aout 2000
if (age>0) {
	if (mois<=8)  {
  age=age+1;
	}else {
  age=age;
	}
 
}else {
  age=0;
}

Ecrire('Age au 31 aout 2000='+age);

age=2000-annee;//Age au 15 aout 2000

if (age>0) {
  if (mois<8)  {
    age=age+1;
  }else if (mois==8 & jour<=15) {
      age=age+1;
    }else {
      age=age;
    }
}else {
  age=0;
}
   
  


Ecrire('Age au 15 aout 2000 =' +age);


