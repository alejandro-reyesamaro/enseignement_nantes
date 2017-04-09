/* 
   GAILLARD Florent
   MONNEAU Dylan 
   601A
*/
#ifndef DONNEES_HPP
#define DONNEES_HPP

/* Structure contenant les données du problème */

struct donnees {
	int nblieux; /* Nombre de lieux (incluant le dépôt) */
	int capacite; /* Capacité du véhicule de livraison */
	int *demande; /* Demande de chaque lieu (la case 0 est inutilisée car le dépôt n'a aucune demande à voir satisfaire) */
	int **C; /* distancier (les lignes et colonnes 0 correspondent au dépôt) */
};

#endif