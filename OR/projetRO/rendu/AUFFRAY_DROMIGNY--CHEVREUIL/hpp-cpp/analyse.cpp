/* Fichier contenant la fonction permettant l'analyse des différentes fonctions par : Auffray Baptiste et Dromigny--Chevreuil Ivan */

#include "analyse.hpp"

using namespace std;

struct timeval start_utime, stop_utime;

void crono_start(){

	struct rusage rusage;
	
	getrusage(RUSAGE_SELF, &rusage);
	start_utime = rusage.ru_utime;
}

void crono_stop(){

	struct rusage rusage;
	
	getrusage(RUSAGE_SELF, &rusage);
	stop_utime = rusage.ru_utime;
}

double crono_ms(){

	return (stop_utime.tv_sec - start_utime.tv_sec) * 1000 +
    (stop_utime.tv_usec - start_utime.tv_usec) / 1000 ;
}


//----------------------------------------------------------------------------------------------------------------

/* Fonction permettant l'analyse des fonctions */
void analyse(){

	// On ouvre le fichier analyse.txt  en écriture
	ofstream file("resultats/analyse.txt");

	if(file){

		int nbTest = 9;

		vector<donnees> res;

		string nom = "A/VRPA";

		file << "Instance A" << endl << endl<< "Temps d'excécution: " << endl;

		file << "nb Lieux\tregrouper()\tTSP1()\t\tTSP2()\t\tTSP3()" << endl << endl;

		// Pour chacune des iinstances du dossier...
		for (int i = 0; i < nbTest; ++i){

			donnees tmp;
			res.push_back(tmp);

			string nomFinal;

			double temps;

			nomFinal = nom + (char)(49+i*0.5) + (char)(48+5*(i%2)) + ".dat";

			// On récupère les informations nécessaires dans la structure donnees
			lecture_data(nomFinal, res[i]);

			file << res[i].nbLieux << "\t\t";

			// On calcule le temps d'exécution de la fonction regrouper()
			crono_start();

				regrouper(res[i]);

			crono_stop();

			// On l'affiche
			temps = crono_ms()/1000;
			file << temps << "\t\t";

			temps = 0;
			
			// On calcule le temps d'exécution de la fonction TSP1()
			crono_start();

				TSP1(res[i]);

			crono_stop();

			// On l'affiche
			temps = crono_ms()/1000;
			file << temps << "\t\t";
			
			// On calcule le temps d'exécution de la fonction TSP2()
			crono_start();

				TSP2(res[i]);

			crono_stop();

			// On l'affiche
			temps = crono_ms()/1000;
			file << temps << "\t\t";

			// On calcule le temps d'exécution de la fonction TSP2()
			crono_start();

				TSP3(res[i]);

			crono_stop();

			// On l'affiche
			temps = crono_ms()/1000;
			file << temps << endl;
		}

		// On créer un vecteur de vecteur d'entier permettant de stocker le nombre de circuits de taille n, pour tout n de 2 à nbL
		vector<vector<int> > circTailleN;
		int x = 10;
		for (int i = 0; i < res.size(); ++i){
			vector<int> tmp;
			circTailleN.push_back(tmp);

			for (int j = 0; j < x; ++j){
				circTailleN[i].push_back(0);
			}
			for (int j = x; j < 50; ++j){
				circTailleN[i].push_back(-1);
			}
			x +=5;
		}
		
		// On remplie le vecteur
		for (int i = 0; i < res.size(); ++i){
			for (int j = 0; j < res[i].nbCirc; ++j){
				circTailleN[i][res[i].circuit[j].size()-1]++;
			}
		}
		

		file << endl <<"Regroupements : " << endl << "nb lieux\t";

		for (int i = 0; i < nbTest; ++i){
			file << "\t" << res[i].nbLieux;
		}

		file << endl << endl << "nb regroupement\t";

		//On affiche le nombre de circuits présent dans chaque instance
		for (int i = 0; i < nbTest; ++i){
			file << "\t" << res[i].nbCirc;
		}

		file << endl << endl;

		// On affiche le nombre de circuit de taille n, pour tout n de 2 à nbL
		for (int i = 0; i < 50; ++i){
			file << i+1  << "\t\t\t";
			for (int j = 0; j < nbTest; ++j){
				file << circTailleN[j][i] << "\t";
			}
			file << endl;
		}

		file << endl << endl;

		// On vide le vecteur de structure et on réitère les opérations précédentes pour les instances du dossier B
		res.clear();

		nom = "B/VRPB";

		file << "Instance B" << endl << endl << "Temps d'excécution: " << endl;

		file << "nb Lieux\tregrouper()\tTSP1()\t\tTSP2()\t\tTSP3()" << endl << endl;

		for (int i = 0; i < nbTest; ++i){

			donnees tmp;
			res.push_back(tmp);

			string nomFinal;

			double temps;

			nomFinal = nom + (char)(49+i*0.5) + (char)(48+5*(i%2)) + ".dat";

			lecture_data(nomFinal, res[i]);

			file << res[i].nbLieux << "\t\t";

			crono_start();

				regrouper(res[i]);

			crono_stop();

			temps = crono_ms()/1000;
			file << temps << "\t\t";

			temps = 0;
			
			crono_start();

				TSP1(res[i]);

			crono_stop();

			temps = crono_ms()/1000;
		
			file << temps << "\t\t";
			

			crono_start();

				TSP2(res[i]);

			crono_stop();

			temps = crono_ms()/1000;
			
			file << temps << "\t\t";

			
			crono_start();

				TSP3(res[i]);

			crono_stop();

			temps = crono_ms()/1000;
			
			file << temps << endl;
			
		}

		circTailleN.clear();
		x = 10;
		for (int i = 0; i < res.size(); ++i){
			vector<int> tmp;
			circTailleN.push_back(tmp);

			for (int j = 0; j < x; ++j){
				circTailleN[i].push_back(0);
			}
			for (int j = x; j < 50; ++j){
				circTailleN[i].push_back(-1);
			}
			x +=5;
		}
		
		for (int i = 0; i < res.size(); ++i){
			for (int j = 0; j < res[i].nbCirc; ++j){
				circTailleN[i][res[i].circuit[j].size()-1]++;
			}
		}
		

		file << endl <<"Regroupements : " << endl << "nb lieux\t";

		for (int i = 0; i < nbTest; ++i){
			file << "\t" << res[i].nbLieux;
		}

		file << endl << endl << "nb regroupement\t";

		for (int i = 0; i < nbTest; ++i){
			file << "\t" << res[i].nbCirc;
		}

		file << endl << endl;

		for (int i = 0; i < 50; ++i){
			file << i+1  << "\t\t\t";
			for (int j = 0; j < nbTest; ++j){
				file << circTailleN[j][i] << "\t";
			}
			file << endl;
		}

		file << endl << endl;
	}
}