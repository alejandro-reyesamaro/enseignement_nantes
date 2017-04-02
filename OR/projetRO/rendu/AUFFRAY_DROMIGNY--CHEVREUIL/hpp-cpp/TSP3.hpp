/* Fichier contenant le header du Voyageur de commerce en GLPK par : Auffray Baptiste et Dromigny--Chevreuil Ivan */

                                                                  
#ifndef TSP3_H                                                                 
#define TSP3_H                                                             
               
#include "structure.hpp"


void ajout_contrainte (glp_prob *voy, std::vector<int> s, int taille);

std::vector<std::vector<int> > regrouper_sc(std::vector<int> sous_circ);

void voyageur(donnees &p, int c);

void TSP3(donnees &p);


#endif //TSP3_H

