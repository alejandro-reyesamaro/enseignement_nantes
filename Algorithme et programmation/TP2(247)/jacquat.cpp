
//jacquat alexandre
//programme permettant de dessiner une maison




#include<iostream>
#include<string>
using namespace std;
// ce programme peut fonctionner qu'avec une valeur impaire superieur à 1
//------------------------------------
void carre(size){//procedure affichant la base carré de la maison
  int i;
  string base;
  string cote;
  base = '+';
  cote = '|';
   if (size%2 == 1){
	for (i=0;i<(size-3);i++){
		base = base + '-';
		cote = cote + ' ';
}
}
  base = base + '+';
  cote = cote + '|';
  cout << base;
  for (j=0;j<(size-3);j++){
	cout << cote;
}
  cout << base;
}
//------------------------------------

void toit(t){// procedure affichant le toit de la maison
  int c;//variable qui va crée l'ecart le long du bord de la page
  int ecart;// variable qui va crée l'ecart entre '/' et '\'
  int i;
  int j;
  ecart=1;
  c=((t-1)/2)-1;
  cout << '*';
  while(c<(t-2)){//boucle qui affiche le toit
	for (i=0;i<(c);i++){
	  cout << ' ';
	}
	cout << '/';
	for (j=0;j<ecart;j++){
	  cout << ' ';
	}
	cout << '\';
	t = t+2;
}
}

//------------------------------------
int main{
  int taille;
  cout << "taille de la maison?";
  cin >> taille;//saisie de la taille
  toit(taille);
  carre(taille);
}
//ce programme ne fonctionne pas
