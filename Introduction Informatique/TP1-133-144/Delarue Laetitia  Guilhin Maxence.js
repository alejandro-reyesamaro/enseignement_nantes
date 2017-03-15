// Delarue Laetitia  Guilhin Maxence E168101T

//Algo calcul age

var annee; var mois; var x; var jour; //entier
annee = Saisie("Entrez votre annee de naissance");
mois = Saisie("Entrez votre mois de naissance en chiffre");
jour = Saisie("Entrez votre jour de naissance");
x = 2020 - annee ; //age en 2020
Ecrire ("Votre age le 31 decembre 2020 sera" + " " + x + " " + "ans.");
x = 2000 - annee; //age en 2000

if (x>=0)
	Ecrire (" Votre age le 31 decembre 2000 était de" + " " + x + " " + "ans.");
else 
	Ecrire("Vous n'étiez pas ne le 31 decembre 2000");

if (x>=0 && mois<=8)
	Ecrire ("Votre age le 31 aout 2000 etait de" + " " + x + " "+ "ans.");
else if (x>0 && mois>8)
	Ecrire ("Votre age le 31 aout 2000 etait de" + " "+ (x-1) +" " + "ans.");
else
  Ecrire ("Vous n'etiez pas ne le 31 aout 2000");

if (x>=0 && mois<8)
  Ecrire ("Votre age le 15 aout 2000 était de"+ " " + x + " " + "ans");
else if ( x>=0 && mois==8 && jour<15) 
  Ecrire ("Votre age le 15 aout 2000 était de"+ " " + x + " " + "ans");
else
  Ecrire ("Vous n'etiez pas ne le 15 aout 2000");


// Delarue Laetitia E161943A
// Guilhin Maxence E168101T

// Algo mot a l'envers

var x;
while (x!="."){
x= Saisie ("Saisir une lettre");
Ecrire ("votre mot a l'endroit est" + " " + x);
}
