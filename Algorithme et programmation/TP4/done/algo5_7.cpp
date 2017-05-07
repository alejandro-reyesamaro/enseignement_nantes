/NGOM MOUHAMADOU. EXO5.7 (PAS EU LE TEMPS DE FAIRE QUELQUES TESTSS ET COMMENTAIRES SUPPLÉMENTAIRES..)
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Cree un nouveau type 'vecteur_reel' qui equivaut a 'vector<double>'
typedef vector<double> vecteur_reel;

unsigned int taille_vecteur(vecteur_reel vec) {

    return vec.size();
}

vecteur_reel saisie_vecteur(void) {

    vecteur_reel vec;
    double val;
    int nbr;

    cout << "Nombre de réel a saisir: ";
    cin >> nbr;

    for(int i = 0; i < nbr; i++) {

        cout << i+1 << "-ieme valeur: ";
        cin >> val;
        vec.push_back(val);
    }

    return vec;
}

void affiche_vecteur(vecteur_reel vec) {

    for(unsigned int i=0; i<vec.size(); i++)
        cout << vec.at(i) << endl;
}


void detruire_vecteur(vecteur_reel vec) {

    // On supprime toutes les cases du vecteur
    while( !vec.empty() )
        vec.pop_back();
}

vecteur_reel copie_vecteur(vecteur_reel vec, unsigned int dim) {

    vecteur_reel copie;

    for(unsigned int i=0; i<dim; i++) {

        // Copie les donnees de vec
        if(i < vec.size())
            copie.push_back(vec.at(i));
        else // Si la taille de vec < dim, on initialise les nouvelles valeurs a 0
            copie.push_back(0);
    }

    return copie;
}

vecteur_reel chargement_vecteur(string fichier_str) {

    // Ouvre un fichier, le lis et copie ses donnees dans vec
    fstream fichier;

    vecteur_reel vec;
    double val;

    fichier.open(fichier_str, ios::in);

    fichier >> val;
    while( !fichier.eof() ) {

        vec.push_back(val);
        fichier >> val;
    }

    fichier.close();

    return vec;
}
// CE QUI EST À RENDRE !!-------------------------------------------------------------------------------------------------------------------------
double produit_scalaire(vecteur_reel vec1, vecteur_reel vec2, bool *err) {

    int somme = 0;
    *err = false;

    //  Test non fait pour  si le produit scalaire peut etre calcule (manque de temps)
    if( (vec1.size() != vec2.size()) || (vec1.size() == 0 || vec2.size() == 0) ) {

        // Une erreur
        *err = true;
        return -1;
    }

    // Calcul du produit scalaire
    for(unsigned int i=0; i<vec1.size(); i++)
        somme = vec1.at(i) * vec2.at(i);

    return somme;
}

int main(void) {

    vector<double> vec1, vec2;
    int a;
    bool err;

    vec1 = saisie_vecteur();
    vec2 = chargement_vecteur("test.txt");

    a = produit_scalaire(vec1, vec2, &err);
    if(err) {

        cout << "Le produit scalaire ne peut etre calcule" << endl;
    } else {

        cout << "Produit scalaire: " << a << endl;
    }

    detruire_vecteur(vec1);
    detruire_vecteur(vec2);

}

