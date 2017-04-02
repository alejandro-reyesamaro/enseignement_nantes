//Angeli Kevin-Gueguen Ronan

//Iteratif

#include <iostream>
using namespace std;

const int N = 10;
typedef int T_tab[N]; //désolé pour la notation

typedef struct{
		int nb;
		T_tab tableau;
} T_tableau;

void decalage(T_tableau tabInitial,T_tableau & tabDecal,int decal)
{
	int ind;
	int pos;
	
	pos = 0;
	
	for (ind = tabInitial.nb-decal ; ind < tabInitial.nb; ind++){
		tabDecal.tableau[pos] = tabInitial.tableau[ind];
		pos++;
	}
	
	for (ind = 0 ; ind < tabInitial.nb; ind++){
		tabDecal.tableau[pos] = tabInitial.tableau[ind];
		pos++;
	}
}

int main()
{
	int ind;
	int decal;
	T_tableau tabInitial;
	T_tableau tabDecal;
	
	cout << "Saisir la longueur du tableau." << endl;
	cin >> tabInitial.nb ;
	
	cout << "Saisir les valeurs du tableau."<< endl; 
	for(ind = 0; ind < tabInitial.nb ; ind ++){
		cin >> tabInitial.tableau[ind];
	}
	
	cout << "Saisir le decalage." << endl;
	cin >> decal;
	if (decal>tabInitial.nb){
		decal = decal - tabInitial.nb;
	}
	
	decalage(tabInitial,tabDecal,decal);
	
	cout << "[";
	for(ind = 0; ind < tabInitial.nb; ind++){
		cout << tabDecal.tableau[ind] << "," ;
	}
	cout << "]" << endl;
	return(0);	
}

/*Test 1:
	nb = 5, tableau =[5,4,3,2,1], decal = 2, tableau = [2,1,5,4,3];
	* 
Test 2:
	nb = 5, tableau =[5,4,3,2,1], decal = 6, tableau = [1,5,4,3,2];
*/

//Recursif
/*//Angeli Kevin-Gueguen Ronan

#include <iostream>
using namespace std;

const int N = 10;
typedef int T_tab[N]; //désolé pour la notation

typedef struct{
		int nb;
		T_tab tableau;
} T_tabEnt;

void decalage(T_tabEnt tabInitial,T_tabEnt & tabDecal,int & decal)
{
	int ind;
	int pos;
	
	pos=0;
	
	if(decal>){
		tabDecal.tableau[tabInitial.nb+1] = tabInitial.tableau[tabInitial.nb];
		decal--;
		decalage(tabInitial,tabDecal,decal);
	else{
		for (ind = 0 ; ind < tabInitial.nb; ind++){
			tabDecal.tableau[pos] = tabInitial.tableau[ind];
			pos++;
		}
	}		
}

int main()
{
	int ind;
	int decal;
	T_tablEnt tabInitial;
	T_tabEnt tabDecal;
	
	cout << "Saisir la longueur du tableau." << endl;
	cin >> tabInitial.nb ;
	
	cout << "Saisir les valeurs du tableau."<< endl; 
	for(ind = 0; ind < tabInitial.nb ; ind ++){
		cin >> tabInitial.tableau[ind];
	}
	
	cout << "Saisir le decalage." << endl;
	cin >> decal;
	if (decal>tabInitial.nb){
		decal = decal - tabInitial.nb;
	}
	
	decalage(tabInitial,tabDecal,decal);
	
	cout << "[";
	for(ind = 0; ind < tabInitial.nb; ind++){
		cout << tabDecal.tableau[ind] << "," ;
	}
	cout << "]" << endl;
	return(0);	
}*/
