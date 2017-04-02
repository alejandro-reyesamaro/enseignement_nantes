/* Fichier d'implémentation du projet par : Auffray Baptiste et Dromigny--Chevreuil Ivan */
  

#include "analyse.hpp"

/* Structures et fonctions de mesure du temps distancesPU */

using namespace std;

//----------------------------------------------------------------------------------------------------------------

/* Fonction principale permettant la résolution du problème */
int main(int argc, char *argv[]){	
	
	/* Déclarations des variables */

	donnees p; 
	double temps;

	if (argv[3] != NULL){
		analyse();
	}
	else{


		/* Structures de données propres à GLPK */
		
		glp_prob *prob; // Déclaration d'un pointeur sur le problème
		

	    /* Variables récupérant les résultats de la résolution du problème (fonction objectif et valeur des variables) */
		
		int z; 
		vector<bool> x; 


		/* Autres déclarations */ 
		
		int nbCreux; // Nombre d'éléments de la matrice creuse
		int pos;	 // Compteur utilisé pour le remplissage de la matrice creuse
			

		/* Chargement des données à partir d'un fichier */
		
		lecture_data(argv[1],p);
		
		/* Lancement de la résolution... */

		crono_start(); // .. et donc du chronomètre

		
		/* Calcul de tous les circuits effectuables par le drone */

		regrouper(p);
		
		/* Calcul du parcours le plus cours pour chaque circuit */

		if (strcmp(argv[2], "1") == 0)
			TSP1(p);
		else if (strcmp(argv[2], "2") == 0)
			TSP2(p);
		else if (strcmp(argv[2], "3") == 0)
			TSP3(p);
		else{
			cout << "Mauvais numéro entré en paramètre" << endl;
			return 0;
		}
		

		/* Les déclarations suivantes sont optionnelles, leur but est de donner des noms aux variables et aux contraintes. */
		
		char nomContr[p.nbLieux-1][15];
		char nomVar[p.nbCirc][15];

		/* Transfert de ces données dans les structures utilisées par la bibliothèque GLPK */
		
		prob = glp_create_prob(); 									// Allocation mémoire pour le problème
		glp_set_prob_name(prob, "Récupération de réserves d'eau"); 	// Affectation d'un nom
		glp_set_obj_dir(prob, GLP_MIN);

		/* Déclaration du nombre de contraintes */
		glp_add_rows(prob, p.nbLieux-1); 

		
		for(int i = 1; i <= p.nbLieux-1; i++){

			/* Partie optionnelle : donner un nom aux contraintes */

			strcpy(nomContr[i-1], "Contrainte ");
			string tmp = to_string(i);
			const char* cstr = tmp.c_str();	
			strcat(nomContr[i-1], cstr);
			glp_set_row_name(prob, i, nomContr[i-1]); // Affectation du nom à la contrainte i
			

			/* Partie indispensable : les bornes sur les contraintes */

			glp_set_row_bnds(prob, i, GLP_FX, 1.0, 0.0); 	// On applique la borne grâce aux paramètres de droite
		}

		/* Déclaration du nombre de variables : p.nbCirc */
		
		glp_add_cols(prob, p.nbCirc);


		/* On précise le type des variables */

		for(int i = 1; i <= p.nbCirc; i++){

			/* Partie optionnelle : donner un nom aux variables */

			strcpy(nomVar[i-1], "x");
			string tmp = to_string(i);
			const char* cstr = tmp.c_str();	
			strcat(nomVar[i-1], cstr);
			glp_set_col_name(prob, i , nomVar[i-1]);

			/* Partie obligatoire : bornes sur les variables */

			glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0);
			glp_set_col_kind(prob, i, GLP_BV);
		} 


		for(int i = 1; i <= p.nbCirc; i++) 
			glp_set_obj_coef(prob,i, p.tailleCirc[i-1]); 

		/* Définition des coefficients non-nuls dans la matrice creuse */

		nbCreux = 0;
		for(int i = 0; i < p.nbLieux; i++) 
			nbCreux += p.contr[i].size();

		/* Déclaration des 3 tableaux servant à définir la matrice "creuse" des contraintes*/
		int *lignes;
		int *colonnes;
		double *valeurs;  
		lignes = (int *) malloc ((1 + nbCreux) * sizeof(int));;
		colonnes = (int *) malloc ((1 + nbCreux) * sizeof(int));;
		valeurs = (double *) malloc ((1 + nbCreux) * sizeof(double));;


		/* Matrice creuse est tableau de circuit, donc on doit calculer les distance totale de chaque circuit */

		pos = 1;
		for(int i = 0; i < p.nbLieux; i++){
			for(int j = 0; j < p.contr[i].size(); j++){
				lignes[pos] = i;
				colonnes[pos] = p.contr[i][j];
				valeurs[pos] = 1.0;
				pos++;
			}
		}


		/* Chargement de la matrice dans le problème */
		
		glp_load_matrix(prob,nbCreux,lignes,colonnes,valeurs); 


		/* Optionnel : écriture de la modélisation dans un fichier (utile pour debugger) */

		glp_write_lp(prob,NULL,"resultats/Drone.lp");

		glp_simplex(prob,NULL);	glp_intopt(prob,NULL); /* Résolution */
		z = glp_mip_obj_val(prob); /* Récupération de la valeur optimale. Dans le cas d'un problème en variables continues, l'appel est différent : z = glp_get_obj_val(prob);*/
		for(int i = 0;i < p.nbCirc; i++) x.push_back(glp_mip_col_val(prob,i+1)); /* Récupération de la valeur des variables, Appel différent dans le cas d'un problème en variables continues : for(i = 0;i < p.nbvar;i++) x[i] = glp_get_col_prim(prob,i+1);	*/

		/* Problème résolu, arrêt du chrono */
		
		crono_stop();
		temps = crono_ms()/1000;
		

		/* Affichage des résultats */
		cout << "z = " << z << endl;

		// Si le nombre de circuit est supérieur à 100 on ne les affiches pas pour éviter de "polluer" le terminal de texte */ 
		if (p.nbCirc < 100){
			for(int i = 0; i < p.nbCirc; i++) {
				cout << nomVar[i] << " = " << x[i] <<  "  Circuit : ";
				for (int j = 0; j < p.circuit[i].size(); ++j){
					cout << p.circuit[i][j] << ", ";
				}
				cout << p.tailleCirc[i] << endl; 
			}
		}

		cout << "Temps : " << temps << endl;
		
		/* Libération mémoire (à compléter en fonction des allocations) */
		glp_delete_prob(prob); 
	}
	
	return 0;
}