/* carvin_savina_maison.cpp − auteurs : B.CARVIN (247T), L.SAVINA (247S)
TD-2 exo 2.2
Role : affiche une maison de largeur donnée, la largeur doit etre impaire
*/
#include <iostream>

using namespace std;

// affiche une ligne du dessin avec les symboles donnés
void tracer_ligne(int nbe, char gche, char milieu, char dte, int nb)
{
		string ligne = ""; // représente la ligne à afficher
		int i;
		
		// ajoute les espaces avant les caractères
		for(i = 1; i <= nbe; i++)
		{
				ligne = ligne + ' ';
		}
		
		// ajoute le caractère de gauche
		ligne = ligne + gche;
		
		// ajoute le/les caractères du milieu
		for(i = 2; i <= nb-1; i++)
		{
				ligne = ligne + milieu;
		}
		
		// ajoute le caractère de droite
		ligne = ligne + dte;
		
		//affiche la ligne
		cout << ligne << endl;
}


// dessine un carré de largeur donnée
void carre(int taille)
{
		int i;
		
		// affiche la ligne du haut
		tracer_ligne(0,'+','-','+',taille);
		
		// affiche les lignes du centre
		for(i = 1; i <= (taille-2); i++)
		{
			tracer_ligne(0,'|',' ','|',taille);
		}
		
		// affiche la ligne du bas
		tracer_ligne(0,'+','-','+',taille);
}


// dessine un triangle (sauf la base) de largeur donnée
void triangle(int taille)
{
		int i, moitie;
		
		// nombre de caractères avant le centre
		moitie = (taille-1)/2;
		
		// affiche l'étoile du milieu
		tracer_ligne(moitie-1,' ','*',' ',3);
		
		// affiche les deux premiers côtés du triangle
		for(i = 1; i <= moitie; i++)
		{
			tracer_ligne(moitie-i,'/',' ','\\',2*i+1);
		}
}

int main()
{
	int nb;
	
	// saisie d'un nombre impair
	do{
	cout << "Nombre impair : ";
	cin >> nb;
	}while(nb % 2 == 0);
	
	// dessin du triangle puis du carré
	triangle(nb);
	carre(nb);
}

/*
cas 1	->
input : 7
output : 
   * 
  / \
 /   \
/     \
+-----+
|     |
|     |
|     |
|     |
|     |
+-----+

cas 2	->
input : 6
input : 5
output :
  * 
 / \
/   \
+---+
|   |
|   |
|   |
+---+

cas 3	->
input : 153
output :
trop grand, ne s'affiche pas correctement

cas 4	->
input : 3.5
output :
 * 
/ \
+-+
| |
+-+

cas 5	->
input : 1
output :
 * 
++
++

cas 6	->
input : -3
ouput : 
 * 
++
++

Conclusion : le programme fonctionne pour des entiers positifs impairs inférieurs à la largeur du terminal.
*/	
