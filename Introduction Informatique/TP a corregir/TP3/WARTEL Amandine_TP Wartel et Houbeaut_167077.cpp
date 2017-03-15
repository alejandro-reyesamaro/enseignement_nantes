//Amandine Wartel-Mélissandre Houbeaut

#include<iostream>

using namespace std;


const int NC=100;

typedef struct 
	{ 
		int contenu[NC]; 
		int nbc; 
	} 
T_tabEnt ;
    
// procédure itérative
void decalage ( int decal , T_tabEnt & tab)
	{
		T_tabEnt tempo;
		int indice;  cout << "entree dans decalage" << endl;
// Recopie du tableau
			for (indice =0; indice <= tab.nbc -1; indice ++)
			{
				tempo.contenu[indice]=tab.contenu[indice];
			}
                             cout << "clonage fait" << endl;
// Restitution avec decalage
			for (indice=0; indice <=tab.nbc -1; indice ++)
			{
				tab.contenu [(indice+decal) % tab.nbc]=tempo.contenu[indice];
			}
                              cout << "decalage fait" << endl;
	}

// procédures récursives
void decalins (T_tabEnt & tabc)
{
	int delta;
	int stock;
	stock =tabc.contenu[tabc.nbc-1];
	for (delta = 1; delta<= tabc.nbc-1; delta++)
		{ 
			tabc.contenu[tabc.nbc-delta]=tabc.contenu[tabc.nbc-delta-1];
		}
        tabc.contenu [0]=stock;
}


void decalage2( int decal, T_tabEnt & tab)
{
	if (decal>=1)
	{
		decalins (tab);
		decalage (decal-1,tab);
	}
}




void affiche_tableau (T_tabEnt table)

{
   int ind;
   for (ind=0; ind<= table.nbc-1; ind ++)
   {
      cout << table.contenu[ind]<<endl;
   }
	cout<< endl;
}


int main()

{
	
	T_tabEnt nombre;
	int i;
	cout<<"Un nombre de cases?" << endl;
	cin >> nombre.nbc;
	i=0;
	
	
        while (i<nombre.nbc)
		{
			cout<<"Saisissez une valeur pour la case "<<i+1<<"du tableau."<<endl;
			cin >> nombre.contenu[i];
			i++;
		}

    decalage (3, nombre);
    cout << "decalage fait" << endl;
    affiche_tableau(nombre);
    decalage2(3,nombre);
    affiche_tableau(nombre);
	return(0); 
}
