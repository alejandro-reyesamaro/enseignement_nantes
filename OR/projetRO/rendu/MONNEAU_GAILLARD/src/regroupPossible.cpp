/* 
   GAILLARD Florent
   MONNEAU Dylan 
   601A
*/

#include "regroupPossible.hpp"

using namespace std;

int ajoutPossible(vector<int> regroup, int valeur, vector<int> demandeCl, int capaciteDrone) {
	/* 
	* accumulateur de la capacité de tous les points d'eau 
	*  la valeur initiale correspond à la capacité du point d'eau à ajouter au regroupement
	*/
	int acc = demandeCl[valeur-1];

	// pour chaque point d'eau du regroupement actuel on ajoute sa capacité en eau
	for (int i=0; i < regroup.size(); ++i)
		acc += demandeCl[regroup[i]-1];
	// On retourne 1 si l'accumulateur a une capacité inférieur ou égale à la capacité du drone sinon 0
	return acc <= capaciteDrone;
}

vector<vector<int> > regroupementPossible(donnees d)
{
	// Vecteur possédant tous les regroupement à la fin de la fonction
	vector<vector<int> > result;
	// Vecteur temporaire permettant de former les regroupements
	vector<int> vec;

	// Vecteur comportant les demandes des clients
	vector<int> demandeCl;
	for(int z=1; z<d.nblieux; ++z)
		demandeCl.push_back(d.demande[z]);

	// Ajout des regroupements de taille 1 (chaque point de pompage)
	for (int i = 1; i <= d.nblieux-1; ++i)
	{
		vec.push_back(i);
		result.push_back(vec);
		vec.clear();
	}
	
	// debut correspondra au début des regroupements précédement créés ici taille 1
	int debut = 0;
	// fin sera toujours égal à la fin de la liste une fois tous les regroupements créés
	int fin = result.size();
	// permettra de récupérer l'élément le plus grand d'un vecteur
	int max;

	// Pour chaque regroupement de taille 2 au nombre de points de pompage
	for (int i = 2; i <= d.nblieux-1; ++i) {
		
		/* Pour chaque regroupement créé précédemment on essaye d'ajouter un nouveau point de pompage
		* pour crééer les regroupement de taille 2 on reprend les regroupement de taille 1
		* pour les tailles 3 ceux de taille 2, etc
		*/
		for (int j = debut; j < fin; ++j)
		{
			// On prend l'élément le plus grand de la liste qui est le dernier car le vecteur est trié par ordre croissant
			max = result[j][result[j].size()-1];
			// De l'élément suivant le maximum au nombre de point de pompage on essaye d'ajouter un nouveau point de pompage
			for (int k = max+1; k <= d.nblieux-1; ++k)
			{
				vec = result[j];
				// Si on peut ajouter le point de pompage au regroupement on l'ajoute à tous les autres regroupements créés
				if(ajoutPossible(vec, k, demandeCl, d.capacite)) {
					vec.push_back(k);
					result.push_back(vec);
				}
			}
		}
		// début prend la valeur de fin correspondant au début des regroupements créés
		debut = fin;
		// fin prend la taille de result
		fin = result.size();
	}
	
	// on retourne tous les regroupements obtenus
	return result;
}