/* Fichier contenant l'implémentation du Voyageur de commerce en GLPK par : Auffray Baptiste et Dromigny--Chevreuil Ivan */


#include "TSP3.hpp"

using namespace std;


//----------------------------------------------------------------------------------------------------------------

/* Fonction permettant de calculer toutes les permutations possibles du sous-circuit */
vector<vector<int> > regrouper_sc(vector<int> sous_circ){

    vector<int> tmp;
    vector<vector<int>> sous_ens;
    sous_ens.push_back(tmp);
    vector< vector<int> > resTmp;
    
    // Pour chacun des lieux 
    for (int i = 1; i <= sous_circ.size(); i++){

    	// On récupère les circuits créés précédement
        resTmp = sous_ens;

        // On ajoute pour chacun d'eux le lieux en cours
        for (int j = 0; j < resTmp.size(); j++) {
            //On récupère le quotient de la variable de décision qui correspond au lieu
            resTmp[j].push_back(i-1); 
        	sous_ens.push_back(resTmp[j]);
        }
        resTmp.clear();
    }
    // On supprime le tous premier vecteur ajouté car ce dernier est vide
    sous_ens.erase(sous_ens.begin());

    // On supprime le tous dernier vecteur ajouté car c'est l'ensemble contenant tout les éléments
    sous_ens.erase(sous_ens.end());

    return sous_ens;
}


//----------------------------------------------------------------------------------------------------------------

/* Fonction permettant l'ajout de contrainte dans la résolution de GLPK */
void ajout_contrainte(glp_prob *voy, vector<int> s, int taille) {

	int lignes[s.size()+1];
	double valeurs[s.size()+1];

	//factorielle qui donne le nombre de permutation à faire sur l'ensemble pour obtenir toute les paires de deux contigus
	unsigned int fact = factorial(s.size()-1);
	
	// On extériorise le cas ou on a qu'un lieu car le bouce for ne peut se lancer avec un fact = 1
	if(s.size() == 1) {
		
		glp_add_rows(voy,1);
		glp_set_row_bnds(voy, glp_get_num_rows(voy),GLP_UP, 0.0, s.size()-1);
		
		lignes[1] = taille*(s[0])+(s[0])+1;
		valeurs[1] = 1.0;
		
		glp_set_mat_row(voy, glp_get_num_rows(voy), 1, lignes, valeurs);		
	
	}else {
		
		for (int a = 0; a < fact; ++a) {
			
			glp_add_rows(voy,1);
			glp_set_row_bnds(voy, glp_get_num_rows(voy),GLP_UP, 0.0, s.size()-1);
			
			
			int pos =1;
			//On ajoute la contrainte qui correspond à la permutation
			for(int i = 1; i < s.size(); ++i) {
				
				// Calcule pour déterminer la position des variables de décision qui entre en jeu dans la contrainte
				lignes[pos] = taille*(s[i-1])+(s[i])+1;  
				valeurs[pos] = 1.0;
				pos++;

			}
			
			lignes[pos] = taille*(s[s.size()-1])+(s[0])+1;
			valeurs[pos] = 1.0;
			
			next_permutation(s.begin(), s.end());
			glp_set_mat_row(voy, glp_get_num_rows(voy), pos, lignes, valeurs);
			
		}
	}	
}


//----------------------------------------------------------------------------------------------------------------

/* Fonction permettant la résolution du Voyageur de commerce par GLPK*/
void voyageur(donnees &p, int c){
	
	//Création du problème
	glp_prob *voy;
	voy = glp_create_prob();

	glp_set_prob_name(voy, "voyageur_de_commerce");
	glp_set_obj_dir(voy, GLP_MIN); // On veut minimiser la distance parcourue

	// Nombre de contraintes pour deux premiers groupes de contraintes : on part 1 fois vers 1 ville et on arrive 1 fois de 1 ville
	int nbContr = 2*p.circuit[c].size(); 

	glp_add_rows(voy, nbContr);

	// Toute les contraintes doivent être égale à 1
	for (int i = 1; i <= nbContr; ++i) {
		glp_set_row_bnds(voy, i, GLP_FX, 1.0, 0.0);
	}


	int nbVar = p.circuit[c].size()*p.circuit[c].size(); // Nombre de chemins entre deux villes possibles
	int tailleRegr = p.circuit[c].size();
	int a = 1; 
	glp_add_cols(voy, nbVar); //Définition du nombre de colonnes


	for(int i = 1; i <= tailleRegr ; ++i) {
		for (int j = 1; j <= tailleRegr; ++j) {

			glp_set_col_bnds(voy, a, GLP_DB, 0.0, 1.0);
			glp_set_col_kind(voy, a, GLP_BV);
			// On entre les valeurs du distancier qui correspond au distance entre chaque ville du regroupement
			glp_set_obj_coef(voy, a, p.distances[p.circuit[c][i-1]][p.circuit[c][j-1]]); 
			a++;
		
		}
	}
	
	// Ceci correspond aux nombres de variables qui entre en jeu dans les contraintes
	int nbCreux = tailleRegr*tailleRegr*2; 

	int lignes[nbCreux];
	int colonnes[nbCreux];
	double valeurs[nbCreux];  


	int pos = 1;
	// Premières contraintes : on part 1 fois de 1 ville
	for(int i = 0; i < tailleRegr; i++){
		for(int j = 0+(i*tailleRegr); j < tailleRegr+(i*tailleRegr); j++){

			lignes[pos] = i + 1;
			colonnes[pos] = j + 1;
			valeurs[pos] = 1.0;
			pos++;
		}
	}

	a = 0; 

	// Secondes contraintes : on arrive 1 fois vers 1 ville
	for(int i = tailleRegr; i < tailleRegr*2; ++i) {
		for(int j = a; j < nbVar ; j=j+tailleRegr) {

			lignes[pos] = i+1;
			colonnes[pos] = j+1;
			valeurs[pos] = 1.0;
			pos++;
		}
		a++;
	}

	//On charge ces contraintes dans la matrices des contraintes
	glp_load_matrix(voy, nbCreux, lignes, colonnes, valeurs);

	//Troisieme contraintes : empêcher les sous_boucles
	vector<vector<int> > sous_ens = regrouper_sc(p.circuit[c]);
	

	for(int i = 0; i < sous_ens.size(); ++i) {

		ajout_contrainte(voy, sous_ens[i], p.circuit[c].size());
	}

	glp_term_out(GLP_OFF); // Empeche l'écriture de glpk dans le terminal
	
	glp_simplex(voy, NULL); // Lancement de la résolution
	glp_intopt(voy, NULL);
	
	glp_term_out(GLP_ON); //Reactive l'écriture de glpk dans le terminal

	double z = glp_mip_obj_val(voy);

	int x[p.circuit[c].size()*p.circuit[c].size()];

	for(int i = 0; i < p.circuit[c].size()*p.circuit[c].size(); ++i) x[i] = glp_mip_col_val(voy, i+1);
	
	/* // Affichage utile au débugage
	cout << "circuit : ";
	for (int i = 0; i < p.circuit[c].size(); ++i){ cout << p.circuit[c][i] << "  ";}
	cout << endl;			
	cout << "z = " << z << endl; //ecriture de la distance minimale
	for (int i = 0; i < p.circuit[c].size()*p.circuit[c].size(); ++i) cout << "x["<<i<<"] = " << x[i] << " | dist : " << glp_get_obj_coef(voy, i+1) << endl; //ecriture du chemin
	*/

	p.tailleCirc.push_back(z+0.5); // Un cast est ajouté

	glp_delete_prob(voy);
}


//----------------------------------------------------------------------------------------------------------------

/* Procedure qui lance pour chaque regroupement un voyageur de commerce avec GLPK */
void TSP3(donnees &p){
	
	for(int i = 0; i < p.circuit.size(); ++i) {
		voyageur(p ,i);
	}
}

