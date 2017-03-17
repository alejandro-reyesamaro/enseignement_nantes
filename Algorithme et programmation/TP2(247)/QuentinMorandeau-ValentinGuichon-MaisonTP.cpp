// Quentin Morandeau : E162046M  et Valentin Guichon : E168158F


//Rôle : le but de cet algortihme est de dessiner une maison carré.
 
#include <iostream>
#include <string>

using namespace std;

//-------------------------------------------------------------------
//Rôle : tracer_ligne permet de dessiner la ligne à une hauteur donnée
void tracer_ligne(int nbe, char gche, char milieu, char dte,int nb)
{

        string ligne;
        int i;
        ligne = "";

        for (i=1; i<= nbe; i++){
                ligne = ligne + " ";
        }
        
        ligne = ligne + gche ;

        for (i=2; i<= nb-1; i++){
                ligne = ligne + milieu ;
        }
        
        ligne = ligne + dte ;
        cout << ligne << endl;
}

//------------------------------------------------------------------
/*Rôle : carre permet de determiner le nombre de ligne à tracer et execute la procédure tracer_ligne le nombre de fois que l'utilisateur a choisi grâce au paramètre taille et dessine la base de la maison*/
void carre(int taille){

        int i;
        i = 2;

        tracer_ligne( 0, '+', '-', '+', taille) ;

        while (i <= taille-1) 
	{
                tracer_ligne(0, '|', ' ', '|', taille) ;
                i = i + 1;
        }

        tracer_ligne( 0, '+', '-', '+', taille) ;
	
}

//--------------------------------------------------------------------
/*Rôle : Dessine le triangle(toit de la maison) grâce à la procédure tracer_ligne et au paramètre taille choisi par l'utilisateur*/
void triangle(int taille) {
        int m, debut ;
        /* m nbre espaces milieu, debut nb espaces debut */
        debut = (taille - 3) / 2 ;
        m = 3 ;
        tracer_ligne(debut, ' ', '*', ' ', m) ;
        while ( debut >= 0) {
                tracer_ligne(debut, '/', ' ', '\\', m);
                debut = debut - 1;
                m = m + 2;
        }
}

//----------------------------------------------------------------------
/*Rôle : permet d'appeler les procédures triangle et carre afin de dessiner la maison entière et également de saisir un nombre de ligne et de colonne*/
int main()
{        
	int nbL;
	cout << "Un nombre de ligne et de colonne : ";
	cin >> nbL;

        triangle(nbL) ;
        carre(nbL);
return(0);
}

/*Jeux d'essais :
	- cas 1 --> nbL = 10
		    la maison n'est pas correctement dessinée car nbL pair
	- cas 2 --> nbL = 209
		    à partir de 209, cela ne fonctionne plus car la limite maximale de caractères du terminale avant un retour à la ligne est de 208 caractères

	- cas 3 --> nbL = 1
		    la maison en resultat n'est pas correctement dessinée, elle ne donne pas de toit du fait du trop peu de ligne affichée
	
	Conclusion : il faut que nbL soit impair, supérieur à 3 et strictement inférieur à 209 sinon la maison n'est pas bien affiché et le toit est décalé quand nbL est pair.
*/
		    

