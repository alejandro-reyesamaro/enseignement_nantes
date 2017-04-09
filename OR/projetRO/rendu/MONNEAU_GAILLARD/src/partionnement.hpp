/* 
   GAILLARD Florent
   MONNEAU Dylan 
   601A
*/
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <glpk.h>

#include "donnees.hpp"

int nbTournee(std::vector<std::vector<int> >, int);

std::vector<int> tourneesPresente(std::vector<std::vector<int> >, int);

void partionnementTournees(std::vector<std::vector<int> >, double*, donnees);