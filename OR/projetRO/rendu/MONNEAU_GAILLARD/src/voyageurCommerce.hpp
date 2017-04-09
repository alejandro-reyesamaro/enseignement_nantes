/* 
   GAILLARD Florent
   MONNEAU Dylan 
   601A
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */
#include <vector>

#include "donnees.hpp"

int retrouverNumeroVariable(std::vector<std::string>, char **, char **);

std::vector<std::vector<std::vector<std::string> > > sousTours(std::vector<std::vector<std::string> >);

double* voyageurDuCommerce(std::vector<std::vector<int> >, donnees);