/*  auteur : David.Potet et Frapper Colin 
Role : Affiche le tableau avec un decalage donné par l'utilisateur  
*/

#include<iostream>

using namespace std;

const int N = 5 ;

typedef int T_tab[N];


// ---------------------------------------------------------------------------------------------------------
// Enregistrement T_tabEnt de tableau contenu et entier nbc 
typedef struct  {
    T_tab contenu ;
    int nbc  ;
}T_tabEnt;


// ---------------------------------------------------------------------------------------------------------
// Version itérative decalage1
void decalage1 (int decal, T_tabEnt &table)
{
        T_tabEnt tempo ;
        int i ;
        for (i=0; i<table.nbc; i++)
        {
                tempo.contenu[i] = table.contenu[i];
        }
        for (i=0; i<table.nbc; i++)
        {
                table.contenu[(i+decal)%table.nbc] = tempo.contenu[i];
        }
}

// ---------------------------------------------------------------------------------------------------------
//Version récursive decalage 

/*
void decalage(int decal, T_tabEnt &tab)
{
        int i ;
        T_tabEnt tempo ;
        if(decal <1)
        {
                
        }
         else 
         {
                 for (i=0; i<tab.nbc; i++)
                {
                        tempo.contenu[i] = tab.contenu[i];
                }
                for (i=0; i<tab.nbc; i++)
                {
                        tab.contenu[(i+1)%tab.nbc] = tempo.contenu[i];
                }
                decalage(decal-1,tab);
         }
}
*/

// ---------------------------------------------------------------------------------------------------------
// Procedure remplir_tableau permettant de remplir le tableau
void remplir_tableau(T_tabEnt &table )
{
          for (int i=0; i<table.nbc; i++)
        {
                cout << "Veuillez remplir le champ n° " << i << endl ;
                cin >>table.contenu[i] ;
        }
}

// ------------------------------------------------------------------------------------------------------
// Procedure affiche_tableau permettant d'afficher le tableau
void affiche_tableau (T_tabEnt table )
{
        for (int i=0; i<table.nbc; i++)
        {
                cout <<"Champ n°"<< i << endl ;
                cout << table.contenu[i] << endl ;
        }
}

// ---------------------------------------------------------------------------------------------------------
// Fonction principale
int main ()
{
        
        T_tabEnt table ;        
        table.nbc =5;
        int decal ;
        remplir_tableau(table);
        cout << "De combien voulez vous decalez positivement ? " << endl ;
        cin >> decal ;
        while (decal <0)
        {
                cout << "De combien voulez vous decalez positivement ? " << endl ;
                cin >> decal ;
        }
        //decalage(decal, table);
        decalage1(decal,table);
        affiche_tableau(table);
}


/* Jeux d'essais : 
        Version iterative :
                - tableau [1,2,3,4,5] (decalage de 0) ----> [1,2,3,4,5]
                - tableau [1,2,3,4,5] (decalage de 1) ----> [5,1,2,3,4]
                - tableau [1,2,3,4,5] (decalage de 3) ----> [3,4,5,1,2]
                
      Version recursive : 
                - tableau [1,2,3,4,5] (decalage de 0) ----> [1,2,3,4,5]
                - tableau [1,2,3,4,5] (decalage de 1) ----> [5,1,2,3,4]
                - tableau [1,2,3,4,5] (decalage de 3) ----> [3,4,5,1,2]
*/
