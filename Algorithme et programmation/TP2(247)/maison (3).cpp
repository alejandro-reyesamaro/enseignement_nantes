// Programme dessinant une maison par Romain Charrier et Adil ouzamou

#include <iostream>
#include <string>
using namespace std;


//------------------------------------------------------
//role affiche nbe espace ,gauche ,(nb-2)milieu et droite


void tracer_ligne(int nbe, const char* gauche, const char*  milieu, const char*  droite, int nb)
{
    string ligne;
    int cpt;
    ligne = "";
    cpt=0;
    while (cpt != nbe){
         ligne = ligne + " ";
         cpt = cpt+1;
    }
    cpt=0;
    ligne = ligne + gauche;
    while (cpt < nb){
         ligne =ligne +milieu;
         cpt=cpt+1;
    }
    ligne=ligne+droite;
    cout << ligne<<endl;
}


//---------------------------------------------------
//role crée un carée avec pour cote taille


void carre(int taille)
{
	int i;
	i=0;
	tracer_ligne(0,"+","-","+",taille-2);
	while (i<taille-2)
	{
		tracer_ligne(0,"|"," ","|",taille-2);
		i=i+1;
	}
	tracer_ligne(0,"+","-","+",taille-2);
}

//-----------------------------------------------------------
//role crée un triangle sans base avec pour longeur de la base  taille


void triangle(int taille)
{
	int nb;
	int espace;
	int i;
	nb=1;
	i=taille;
	espace=(i-3)/2;
	tracer_ligne(espace," ","*"," ",nb);
	while (i>2){
		espace=(i-3)/2;
		tracer_ligne(espace,"/"," ","\\",nb);
		i=i-2;
		nb=nb+2;
	}
}

//--------------------------------------------------------------
//fonction principale 
//condition prendre coté impair

int main() 
{
  int cote;
  cout << "svp saisir cote impair"<< endl;
  cin >> cote;
  triangle(cote);
  carre(cote);
}
/*
pour taille = 5
  * 
 / \
/   \
+---+
|   |
|   |
|   |
+---+

pour taille = 21
          * 
         / \
        /   \
       /     \
      /       \
     /         \
    /           \
   /             \
  /               \
 /                 \
/                   \
+-------------------+
|                   |
|                   |
|                   |
|                   |
|                   |
|                   |
|                   |
|                   |
|                   |
|                   |
|                   |
|                   |
|                   |
|                   |
|                   |
|                   |
|                   |
|                   |
|                   |
+-------------------+
*/

 
