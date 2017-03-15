//Exercice 1 :

//Variables
var jour, mois, annee;

//Début
jour = Saisie("Votre jour de naissance");
mois = Saisie("Votre mois de naissance");
annee = Saisie("Votre année de naissance");

while (annee>=2020){
	Ecrire("Veuillez saisir une valeure inférieure à 2020");
	annee = Saisie("Votre année de naissance");
}
Ecrire("Votre âge le 31 décembre 2020 sera "+(2020-annee)+"ans");

if (annee>2000){
	Ecrire("Vous êtes trop jeune");
}
else{
	Ecrire("Votre âge le 31 décembre 2000 sera "+(2000-annee)+"ans");
	if (mois>8){
				Ecrire("Votre âge le 31 aout 2000 sera "+(2000-annee-1)+"ans");
				Ecrire("Votre âge le 15 aout 2000 sera "+(2000-annee-1)+"ans");
				}
	else{
				Ecrire("Votre âge le 31 aout 2000 sera "+(2000-annee)+"ans");
				if (jour>=15){
								Ecrire("Votre âge le 15 aout 2000 sera "+(2000-annee)+"ans");
								}
				else{
								Ecrire("Votre âge le 15 aout 2000 sera"+(2000-annee-1)+"ans");
					}
		}
}
//Fin



//Exercice 2:

//Variables
var annee,jourAnnee;

//Début

annee=Saisie("Veuillez saisir l'année");
mois=Saisie("Veuillez saisir le mois");

if(mois%2==0){
  
  if(mois==2){
			if (annee%4==0 && annee%400!=0 ||annee%400==0){
				Ecrire("Il y a 28 jours");
   
	} 
			else{
				Ecrire("Il y a 29 jours");
				}
    }
	else{
    Ecrire("Il y a 30 jours");
  
		}
    }
 
else{
 Ecrire("Il y a 31 jours"); 
}

//Fin

//Exercice 3

//Variables
var n;

//Début
n=Saisie("Veuillez saisir le nombre de cotés du polygones");
Initialiser();
Couleur('red');
Deplacer(500,500);
for(i==0;i<n;i++){ 
  Avancer(100);
	Droite(360/n);
}
//Fin