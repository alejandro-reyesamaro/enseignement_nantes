/*Algo 2.2 :Maison.  BOULKHEMAIR Issa et PENAULT Samuel*/

//Rôle du programme : Prend un entier impair et dessine une maison, composé d'un carré et d'un triangle ayant tous deux pour base ce nombre

//PRECONDITION : Le programme ne tolère que des nombres impair

#include <iostream>

using namespace std;

//-----------------------------------------------------
// rôle :  dessine un triangle
void triangle(int l){
  int m;
  int i;
  
  m = (l-1)/2;
  for (i=1; i<=m; i++){
	cout <<" ";
  }
  cout << "*" << endl;
  for (int j=2; j <= l; j=j+2) {
	for (i=1; i <= (m-(j/2)); i++){
		cout << " ";
	}
	cout << "/";
	for (int i=(m+1-(j/2));i<=(m-1+(j/2));i++){
		cout << " ";
	}
	cout << "\\" << endl;
  }
}

//-----------------------------------------------------
// rôle :  dessine "+", puis l-2 "-", puis "+"
void ligne1 (int l){
  int i;
  cout << "+";
  for (i=2; i < l; i++){
    cout << "-";
  }
  cout << "+" << endl;
}

//-----------------------------------------------------
// rôle : dessine "|"puis l-2 " " puis "|"
void ligne2 (int l){
  cout << "|";
  for (int i=2;i<l;i++){
    cout << " ";
  }
  cout << "|" << endl;
}

//-----------------------------------------------------
// rôle : dessine un carre dont la forme est faite avec des +,-,| et la zone centrale en espace

void carre(int l) {
  ligne1 (l);
  for(int i=2; i<l; i++){
    ligne2 (l);
  }
  ligne1 (l);
}

//-----------------------------------------------------
// rôle : dessine une maison 

int main()
{
  int nb;
  do {
    cout << "Entrez le côté souhaité : ";
    cin >> nb;
  } while(nb%2 == 0);
  triangle(nb);
  carre(nb);
}
//------------------------------------------------------
/*Tests
nb=3 : fonctionne, rend une maison bien proportionnée :
 *
/ \
+-+
| |
+-+

nb=7 : fonctionne, rend une maison bien proportionnée :
   *
  / \
 /   \
/     \
+-----+
|     |
|     |
|     |
|     |
|     |
+-----+

nb=1 : rend une figure trop petite, il n'y a pas de "barres" :
*
++
++

nb=871 : la fenetre est trop petite, le terminal fait des retours à la ligne indésirable lors de l'affichage de la maison
donc un fonctionnement correct est donc dependant de la taille du terminal

nb=-1 : le programme réagit comme pour nb=1
nb=-5 : le programme réagit comme pour nb=1
*
++
++

nb=1.7 : le programme réagit comme pour nb=1
* 
++
++

nb=8.4 : le programme réagit très mal, comme un nombre pair
nb=7.8 : le programme réagit comme pour nb=7
   *
  / \
 /   \
/     \
+-----+
|     |
|     |
|     |
|     |
|     |
+-----+
 
 
Conclusion : Le programme fonctionne sauf dans les cas extreme :
	* 1 
	* les nombres trop grand pour la taille du terminal
	* les nombres négatifs, car ils font s'executer une fois les boucles "pour"
	* les nombres réel ne sont pas détecté, et traité selon leur partie entière
*/
