/* Fichier contenant l'implémentation du Voyageur de commerce en Brute Force par : Auffray Baptiste et Dromigny--Chevreuil Ivan */

#include "TSP1.hpp"

using namespace std;


//----------------------------------------------------------------------------------------------------------------

/* Algorithme du voyageur de commerce en Brute Force */
void TSP1(donnees &p){

	for (int i = 0; i < p.nbCirc; ++i){

		vector<int> tab;
		int nbLieuxCirc = p.circuit[i].size();
		int distMin = 0;

		// On calcule le parcours du circuit dans l'ordre croissant des lieux et on stock le résultat dans une variable
		for (int j = 0; j < nbLieuxCirc-1; ++j)
			distMin += p.distances[p.circuit[i][j]][p.circuit[i][j+1]];

		distMin += p.distances[p.circuit[i][nbLieuxCirc-1]][0];

		// Si il existe plus d'un (hormis le lieu de départ) alors...
		if (nbLieuxCirc > 2){ 

			int fact = factorial(p.circuit[i].size()-2);
			
			// ... pour chaque cas où l'on démarre par ce lieux (excepté la base)... 
			for (int j = 0; j < nbLieuxCirc-1; ++j){

				//... on fait tous les cas possibles
				for (int k = 0; k < fact; ++k){

					bool test = false;

					// Si le nombre fini avec un des nombres dans le vector tab cela veut dire que c'est l'inverse d'un nombre déjà testé
					// donc on le saute
					for (int l = 0; l < tab.size(); ++l){
						if (p.circuit[i].back() == tab[l]){
							test = true; 
							break;
						}
					}	

					if (!test){

						// On calcule la distance du parcours	
						int tmp = 0;
						for (int j = 0; j < nbLieuxCirc-1; ++j)
							tmp += p.distances[p.circuit[i][j]][p.circuit[i][j+1]];

						tmp += p.distances[p.circuit[i].back()][0];
						
						// Si celle-ci est plus petite que la distance actuelle calculé elle la devient
						if(tmp < distMin)
							distMin = tmp;
					}

					// On passe à la permutation suivante
					next_permutation(p.circuit[i].begin()+1, p.circuit[i].end());
				}
				
				// On refait un permutation inverse, sinon le p.circuit[i][1] retourne le mauvais élément
				prev_permutation(p.circuit[i].begin()+1, p.circuit[i].end());

				// On ajoute le nombre actuelle dans le tableau car l'on vient d'effectuer tous les cas où l'on commence par ce nombre
				tab.push_back(p.circuit[i][1]);	
				next_permutation(p.circuit[i].begin()+1, p.circuit[i].end());
			}
		}

		// On ajoute le résultat final dans la structure donnees
		p.tailleCirc.push_back(distMin);

		// On retrie le tableau (cela n'est pas vraiment nécessaire)
		sort(p.circuit[i].begin(), p.circuit[i].end());
	}
}