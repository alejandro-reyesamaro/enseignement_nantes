Sarah IVANIUK
Matthieu ROYER




// Algorithme age 31 decembre 2020
var annee, age;
annee=Saisie("veuillez saisir l'annee actuelle");
age=2020-annee;
Ecrire("Vous avez"+age+"ans");




// Algorithme age 31 decembre 2000
var annee, age;
annee=Saisie("veuillez saisir l'annee actuelle");
age=2000-annee;
Ecrire("Vous avez"+age+"ans")




// Algorithme nombre de jours
var mois, annee, nbrejrs;
annee=Saisie("Veuillez saisir l'annee actuelle");
mois=Saisie("Veuillez saisir le numero du mois actuel");
if (mois==1 || mois==3 || mois==5 || mois==7 || mois==8 || mois==10 || mois==12)
{
  nbrejrs=31;
  Ecrire("nombre de jours"+"="+"31");
}

  
if (mois==4 || mois==6 || mois==9 || mois==11)
{
 nbrejrs=30;
 Ecrire ("nombre de jours"+"="+"30");
}

if (mois==2)
{
  if  (annee % 400==0 || (annee % 4==0 && annee % 100 !=0)) 
  {nbrejrs=29;
  Ecrire("nombre de jours"+"="+"29");}
  else {nbrejrs=28;
  Ecrire("nombre de jours"+"="+"28");}
}




