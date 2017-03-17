// 247 
//Tom Perroux   François Camelin
// TP 14/03/2016 La maison TD n°2 Exercice 2.2
// Dessin d'un maison en caractères

#include <iostream>
#include <string>
using namespace std;
 // creer une chaine de caracteres g à gauche m au millieu et d a droite de longueur longeur pour le carre
 // et l'affiche
void lignecarre ( char g, char d, char m, int longeur){
	string chaine;
	chaine= g;
	int i;
	
	for ( i = 1; i <(longeur-1); i++){
		chaine= chaine+m;
	}
	chaine=chaine+d;
	cout<<chaine << endl;
}
// creer la ligne pour le triangle
// et l'affiche
void lignetriangle (int decg,char g, char d, char m, int l){
	string chaine;
	int i,j;
	chaine ="";
	for( i = 1 ; i <= decg; i++){
	chaine=' '+chaine;
	} 
	chaine= chaine+g;
	
	for ( i = 1; i <(l-3); i++){
		chaine= chaine+m;
	}
	
	chaine=chaine+d;
	cout<<chaine << endl;
}
// procedure  d'un carre de hauteur hauteur et de largeur impair largueur avec les caractères '+' et '-'
void  carre(int largeur,int hauteur){
	int i;
	lignecarre('+','+','-',largeur);
	for( i = 1; i<(hauteur-1) ; i++){
		lignecarre('|','|',' ',largeur);
		
	}
	lignecarre('+','+','-',largeur);
}
// creer un triangle de lbase l
void triangle( int l){
	int i;
	lignecarre(' ','*',' ',((l-1)/2)+1);
	for( i = 1; i <(l-1)/2 ;i++){
		lignetriangle((((l-1)/2)-i),'/','\\',' ',l);
	}
	lignecarre('/','\\',' ',l);
}
//creer la maison de largeur  5 et de hauteur 7
int main(){
	int hauteur, largeur;
	cout<< ("hauteur de la maison?");
	cin>> hauteur;
	cout<< ("largeur de la maison? ");
	cin>> largeur;
	triangle(largeur);
	carre(largeur,hauteur);
	
}
 
