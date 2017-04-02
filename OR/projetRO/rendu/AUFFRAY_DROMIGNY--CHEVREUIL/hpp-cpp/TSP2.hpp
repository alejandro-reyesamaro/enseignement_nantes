/* Fichier contenant le header du Voyageur de commerce par le NUS par : Auffray Baptiste et Dromigny--Chevreuil Ivan */

                                                                             
#ifndef TSP2_H                                                                  
#define TSP2_H                                                                  
               
#include "structure.hpp"


struct voyage{

	std::vector<std::vector<int> > dist;		// Matrice contenant les distances entres les lieux
	std::vector<std::vector<int> > parcours;		 
	int nbLieuxCirc;							// Nombre de lieux contenu dans le circuit
	int nbLieuxCircPow;							// 2 à la puissance du nombre de lieux contenu dans le circuit
	int circ;									// Circuit actuel
};

int TSPfromNUS(int start, int set, voyage &v, donnees &p);

void TSP2(donnees &p);


#endif //TSP2_H