/* Dousset Teddy et Pacaud Alexandre
 * groupe 243
 * TP n°5 - 5.7 - n°8 et 9
 * 
 * Rôle du programme : Calcul le produit scalaire
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std ;
	
	struct vecteur{                          // type vecteur : taille + coordonnees
		int nb;
		float * ptr;
	};


	void Detruire_Vecteur(vecteur & V){      // Desallouer un vecteur
		delete [] V.ptr;
	}

	vecteur Saisie_vecteur(int nb){          // Saisie d'un vecteur dont on connait la taille
		int i;
		vecteur V;
		V.ptr = new float[nb];
		for(i=0; i<nb; i++){
			cout << "Saisissez la coordonnee_" << i << " :" <<endl;
			cin >> V.ptr[i];
		}
		V.nb = nb;
		return V;
	}
	
	
	float Produit_scalaire(vecteur U, vecteur V){  // Calcul du produit scalaire de 2 vecteurs quand cela est possible
		float res = 0;
		int i;
		if(V.nb!=U.nb){
			cout << "Vecteurs de dimension differentes : valeur initialisee a 0." <<endl;
			return res;
		} else {
			for(i=0; i<V.nb; i++){
				res += V.ptr[i]*U.ptr[i];
			}
			return res;
		}
	}
	
	
	
	
int main () {
	
	float j;
	int i, nb=0;
	fstream flux;
	string source;
	vecteur U, V;
	
	
	
	source = "a.txt";                     // Nom du fichier contenant les coordonnees d'un vecteur
	
	flux.open(source.c_str(), ios::in);   // ouverture du fichier en lecture
	
	if (flux) {                           // On vérifie si l'ouverture du fichier est possible
		flux >> j;	
		while ( !( flux.eof() ) ){        // On compte le nombre d'éléments du fichier source (taille du vecteur)
			nb++;
			flux >> j;
		}
		flux.close();
		U.nb = nb;
		flux.open(source.c_str(), ios::in);
		U.ptr = new float[nb];
		for(i=0; i<nb; i++){                       // On cree un vecteur a partir des valeurs du fichier
			flux >> U.ptr[i];
		}
		flux.close();
	} else {
		cout << "\nImpossible d'ouvrir le fichier source. \n";
	}
	
	cout << "Combien de coordonnees possede votre vecteur" <<endl;
	cin >> nb;
	V = Saisie_vecteur(nb);
	cout << "Le produit scalaire est :" << Produit_scalaire(V, U) <<endl;
	
	Detruire_Vecteur(U);                          // On desalloue les vecteurs
	Detruire_Vecteur(V);
	
	return(0);
}


/*---------------JEU D'ESSAIS-----------------------------------------------
 * 
 * Test n°1 :
 *   U = ( 1 ; 0 )
 *   V = ( 0 ; 1 )
 *   affichage : "Le produit scalaire est : 0"
 * 
 * Test n°2 :
 *   U = ( 1 ; 2 ; 3 ; 4)
 *   V = ( 5.4 ; -1 ; 5 ; -9)
 *   affichage : "Le produit scalaire est : -17.6" 
 * 
 * Test n°3 :
 *   U = ( 1 ; 2 ; 3 ; 4 )
 *   V = ( 0 ; 1 )
 *   affichage : "Vecteurs de dimension differentes : valeur initialisee a 0. 
 *                Le produit scalaire est : 0"
 *---------------------------------------------------------------------------
 */ 
