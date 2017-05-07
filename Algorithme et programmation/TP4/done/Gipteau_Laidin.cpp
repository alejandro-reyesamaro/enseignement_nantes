/* Groupe 243 - LAIDIN Tino, GIPTEAU Thibaut - TD5, exercice 5.7
Rôle : 	Calcul le produit scalaire entre un vecteur saisi pas l'utilisateur et
		un vecteur contenu dans un fichier*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct T_vecteur 
{
	int taille ;
	int *ptab ;
};

T_vecteur saisie_vecteur()
{
	T_vecteur v;
	int i;
	cout << "Quelle est la taille de votre vecteur ?" << endl;
	cin >> v.taille ;
	v.ptab= new int[v.taille]; // allocation d'un tableau d'entier
	for(i=0 ; i<=v.taille-1 ; i++)
	{
		cout << "coordonnée numéro " << i+1 << endl;
		cin >> v.ptab[i]; // saisie des coordonnées du vecteur
	}
	return(v);
}

void affiche_vecteur(T_vecteur vecteur)
{
	int i;
	
	cout << "(" << vecteur.ptab[0];
	
	for(i=1;i<=vecteur.taille-1;i++)
	{
		cout << ";";
		cout << vecteur.ptab[i];
	}
	
	cout << ")"<<endl;
}

void desallocation(T_vecteur vecteur)
{
	delete[] vecteur.ptab; // désalloue la mémoire attribuée à un vecteur
}

T_vecteur chargement_vecteur(string nom)
{
	fstream lecture;
	int taille,tmp;
	T_vecteur v;
	
	taille=0;
	lecture.open(nom.c_str(), ios::in);
	
	if(lecture)
	{
	  lecture >> tmp;
		while (!(lecture.eof())) 
      {
        taille++; 
        lecture >> tmp;
      } // compte du nombre de coordonnées du vecteur contenu dans un fichier
      lecture.close();
	}
	else
	{ 
		cout << "Le fichier n'a pas pu être ouvert " << endl;
	}
	
	v.ptab=new int[taille]; // allocation d'un tableau d'entier
	v.taille=taille;
	
	taille=0;
	lecture.open(nom.c_str(), ios::in);
	
	if(lecture)
	{
		while (!(lecture.eof())) 
      {
		lecture >> v.ptab[taille];
        taille++;
      }
      lecture.close();
	}
	else
	{ 
		cout << "Le fichier n'a pas pu être ouvert " << endl;
	}
	return(v);
}

float produit_scalaire(T_vecteur v,T_vecteur w)
{
	int i;
	float scal=0;
	if(v.taille==w.taille)
	{
		for(i=0;i<=v.taille-1;i++)
		{
			scal+= (w.ptab[i])*(v.ptab[i]);
		}
		return (scal);
	}
	else
	{
		return NULL;
	}
}

int main()
{
	T_vecteur v, w ;
	string nom;
	float scal;
	
	cout << "Quelle est le nom du fichier à charger ? " << endl;
	cin >> nom;
	w=chargement_vecteur(nom);
	
	v=saisie_vecteur();
	cout <<endl;
	
	scal=produit_scalaire(v,w);
	
	if (scal == NULL)
	{
		cout<<"Les deux vecteurs ne font pas la même taille ; erreur" <<endl;
	}
	else 
	{
		cout << "vecteur n°1 : ";
		affiche_vecteur(v);
		cout << "vecteur n°2 : ";
		affiche_vecteur(w);
	
		cout << "Le produit scalaire vaut : " << scal << endl;
	}
	
	desallocation(v);
	desallocation(w);
	
	return(0);
}

/* JEU D'ESSAIS
 * input saisie : 3 1 1 1
 *       fichier : 2 2 2
 * output : 6
 * 
 * input saisie : 2 1 1
 *       fichier : 2 2 2
 * output : Les deux vecteurs ne font pas la même taille ; erreur
*/
