/* Fichier contenant l'implémentation du Voyageur de commerce résolue par l'algorithme du NUS par : Auffray Baptiste et Dromigny--Chevreuil Ivan */


#include "TSP2.hpp"

using namespace std;


//----------------------------------------------------------------------------------------------------------------

/* Algorithme du voyageur de commerce en Branch and Bound */
int TSPfromNUS(int start, int set, voyage &v, donnees &p){

	int masked, mask, result = -1, temp;

	// Si la distance entre le point de départ et le point d'arrivé et différent de -1 c'est qu'on est arrivé à destination donc on retourne la valeur
	if (v.dist[start][set]  != -1){
		return v.dist[start][set];
	}
	// Sinon...
	else{

		// Pour chaque lieux du circuit
		for (int i = 0; i < v.nbLieuxCirc; ++i){

			mask = v.nbLieuxCircPow - 1 - (int)pow(2,i);
			masked = set & mask;
	
			// Si le masked est différent du set c'est qu'on passe dans un branche non visité
			if (masked != set){

				// Dans ce cas on calcule la distance 
				temp = p.distances[p.circuit[v.circ][start]][p.circuit[v.circ][i]] + TSPfromNUS(i, masked, v, p);
		
				// Si le résultat est égale à -1 ou qu'il est supérieur à la variables temporaire, il prend la valeur de la variable temporaire
				
				if (result == -1 || result > temp){
					result = temp; 
				}

				// On ajoute dans le tableau des parcours à l'endroit correspondant 
				v.parcours[start][set] = i;
			}
		}
	}
	
	v.dist[start][set] = result;

	// On retorune a distance
	return result;
}


//----------------------------------------------------------------------------------------------------------------

/* Fonction permettant l'instanciation de la structure "voyage", utile à la résolution du voyageur de commerce grâce à la fonction TSPfromNUS */
void TSP2(donnees &p){

	// Pour chaque circuit on instancie une structure de données avec les informations nécessaires
	for (int i = 0; i < p.nbCirc; ++i){

		voyage v;
		v.nbLieuxCirc = p.circuit[i].size();
		v.nbLieuxCircPow = (int)pow(2,p.circuit[i].size());
		v.circ = i;

		// Pour chaque lieux on instancie deux vecteurs d'entiers
		for (int i = 0; i < v.nbLieuxCirc; ++i){

			vector<int> tmp;
			vector<int> tmp2;

			v.dist.push_back(tmp);
			v.parcours.push_back(tmp2);

			for (int j = 0; j < v.nbLieuxCircPow; ++j){
				v.dist[i].push_back(-1);
				v.parcours[i].push_back(-1);
			}
		}

		// On instancie la matrice des distances avec les distance de la base à chaque lieux
		for (int i = 0; i < v.nbLieuxCirc; ++i){
			v.dist[i][0] = p.distances[p.circuit[v.circ][i]][p.circuit[v.circ][0]];
		}

		// On lance la résolution du problème qui sera automatiquement stocké dans la structure donnees
		p.tailleCirc.push_back(TSPfromNUS(0, v.nbLieuxCircPow - 2, v, p));
	}
}