/* 
Maison.cpp - Auteurs: AUVRAY Cédric, ORTHION Danny. 

Rôle: Affiche une maison composée d'un triangle sans base et d'un carré à partir d'une taille donnée (impaire), en caractères.
*/

#include <iostream>
#include <string>

using namespace std;

string carre(int taille);
string toit(int taille);

/*
rôle: retourne une chaine de caractère chres, qui comportera des caractères, et des caractères retour ligne. Une fois affiché en sortie texte, cela produira un carré.
*/
string carre(int taille){
	string chres; //la chaine qui sera retournée.
	chres="";
	int i,j; //i est le compteur du nombre de "lignes" et j le compteur du nombre de caractères par "ligne".
	
	// parcours le nombre de "lignes" dont sera constituée la chaine chres d'après la taille entrée en paramètre. 
	for(i=1;i<=taille;i++){ 

		//si sont considerées la première ou derniere "ligne", détermine les bords haut et bas du carré et les coins.
		if(i==1 || i==taille){

			chres=chres+"+";
			for(j=1; j <= taille-2; j++){
				chres=chres+"_";
			}
			chres=chres+"+";
			chres=chres+'\n'; 
		}
		//considère toute les autres "lignes" et détermine les bords gauche et droite du carré.
		else{

			chres=chres+"|";
			for(j=1; j <= taille-2; j++){
				chres=chres+" ";
			}
			chres=chres+"|";
			chres=chres+'\n';
		}
	}
	return(chres);
}

/*
rôle: retourne une chaine de caractère chres, qui comportera des caractères, et des caractères retour ligne. Une fois affiché en sortie texte, cela produira un triangle sans base.
*/
string toit(int taille){

	string chres;
	chres="";
	int centre; //entier qui détermine la position du "sommet" du triangle sans base.
	centre=(taille/2)+1;
	int i,j; //i est le compteur du nombre de "lignes" et j le compteur du nombre de caractères par "ligne".

	for(i=1;i<=centre;i++){ //le nombre de "lignes" du triangle correspond à la largeur/2+1 car le côté en paramètre sera impair.

		if(i==1){ // considère la première ligne et détermine la position du sommet dans la chaine retour.
			for(j=1;j<=taille;j++){
				if(j==centre){
					chres=chres+"*";
				}
				else{
					chres=chres+" ";			
				}		
			}
			chres=chres+'\n';	
		}
		else{ //considère toutes els autres lignes pour déterminer la position dans la chaine retour des '/' et '\'
			for(j=1;j<=taille;j++){
				if(j==centre-(i-1)){
					chres=chres+"/";
				}
				if(j==centre+(i-2)){
					chres=chres+'\\';
				}
				else{
					chres=chres+" ";		
				}	
			}
			chres=chres+'\n'; // ce caractère permet d'ajouter un retour à la ligne à la chaine retour afin de ne pas voir de décalage a l'affichage.	
		}
	}
	return(chres);
}

int main(){

	int taille;
	string ch;
	ch="";

	cout << ("côté du carré. (entrez un nombre impair)");
	cin  >> taille;
	// on force ici l'entrée utilisateur pour avoir un nombre forcément impair.
	while(taille%2==0){
		cout << ("Entrée invalide. Veuillez recommencer.");
		cin  >> taille;
	}
	ch=ch+toit(taille);
	ch=ch+carre(taille);
	cout << ch;

}

/*
conclusion: 
les compteurs i et j ont du être déclarés au préalable pour être compilés correctement.
jeux de test: 4,6,9,7,10,21,91,112.
ATTENTION le bon affichage dépend de la taille du terminal dans lequel sera compilé l'éxécutable. 
*/
