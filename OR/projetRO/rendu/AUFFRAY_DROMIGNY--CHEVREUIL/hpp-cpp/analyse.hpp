/* Fichier header de la fonction permettant l'analyse des différentes fonctions par : Auffray Baptiste et Dromigny--Chevreuil Ivan */

#ifndef ANALYSE_H                                                                  
#define ANALYSE_H


#include <time.h>
#include <sys/time.h>
#include <sys/resource.h> /* Bibliothèques utilisées pour mesurer le temps distancesPU */

#include "TSP1.hpp"
#include "TSP2.hpp"
#include "TSP3.hpp" 

void crono_start();

void crono_stop();

double crono_ms();

void analyse();

#endif //ANALYSE_H