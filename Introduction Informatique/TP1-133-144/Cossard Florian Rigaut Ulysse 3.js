// Cossard Florian Rigaut Ulysse 

// Algorithme : Verlan
// Variables
var c, chaine;

// Début
c = Saisie('Première lettre : ');
chaine = '';

while(c != '.')
{
  chaine = c + chaine;
  c = Saisie('Lettre suivante : ');
}

Ecrire(chaine + '.');
// Fin

