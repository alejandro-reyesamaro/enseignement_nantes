/* Fichier d'implémentation de toutes les structures et fonctions communes aux différentes fonctions par : Auffray Baptiste et Dromigny--Chevreuil Ivan */

#include "structure.hpp"

using namespace std;


//----------------------------------------------------------------------------------------------------------------

/* Fonction pour calculer le factoriel d'un nombre */
unsigned int factorial(unsigned int n) {
    if (n == 0)
       return 1;
    return n * factorial(n - 1);
}


//----------------------------------------------------------------------------------------------------------------

/* Lecture des donnees */

void lecture_data(string file, donnees &p){

	ifstream fichier(file);
	
	int val;

	
	if(fichier){

		/* Lecture du nombre de lieux */
		fichier >> p.nbLieux;
		
		/* Lecture de la capacité de contenance du drone*/
		fichier >> p.capacite;
		
		/* Lecture des quantites d'eau des lieux */
		
		for(int i = 1; i < p.nbLieux; i++){
			fichier >> val;
			p.quantite.push_back(val);
		}
        
		/* Lecture du distancier */

		for(int i = 0; i < p.nbLieux; i++){

			vector<int> tmp;
			vector<int> tmp2;
			p.distances.push_back(tmp);
			p.contr.push_back(tmp2);
			for(int j = 0; j < p.nbLieux; j++){

				fichier >> val;
				p.distances[i].push_back(val);
			}
		}
		fichier.close();
	}
	else{
		cout << "Nom de fichier incorrect" << endl;
	}
}


//----------------------------------------------------------------------------------------------------------------s

/* Fonction permettant de calculer tous les circuits possible */

void regrouper(donnees &p){

    vector<int> tmp;
    p.circuit.push_back(tmp);
    int numVar = 1;

    // Pour chacun des lieux 
    for (int i = 1; i < p.nbLieux; i++){

    	// On récupère les circuits créés précédement
        vector<vector<int> > resTmp = p.circuit;

        // On ajoute pour chacun d'eux le lieux en cours
        for (int j = 0; j < resTmp.size(); j++)
            resTmp[j].push_back(i);

        // Pour chacun des nouveaux circuits créé
        for (int j = 0; j < resTmp.size(); j++){

        	int quantEau = 0;

        	// On calcule la quantité d'eau totale
        	for (int k = 0; k < resTmp[j].size(); ++k){
 
        		quantEau += p.quantite[resTmp[j][k]-1];
        	}

        	// Si elle est infèrieure à la capacité du drone on enregistre le circuit
        	if (quantEau <= p.capacite){

        		p.circuit.push_back(resTmp[j]);
        	}
        }
    }

    // On supprime le tous premier vecteur ajouté car ce dernier est vide
    p.circuit.erase(p.circuit.begin());

    // On enregistre le nombre de circuit dans la structure donnees
    p.nbCirc = p.circuit.size();

    // On créé le tableau utile à la création de la matrice creuse
    for (int i = 0; i < p.nbCirc; ++i){
    	p.circuit[i].push_back(0);
    	sort(p.circuit[i].begin(), p.circuit[i].end());

    	for (int j = 1; j < p.circuit[i].size(); ++j){
    	   	p.contr[p.circuit[i][j]].push_back(numVar);
    	}   	
    	numVar++;
    }
}