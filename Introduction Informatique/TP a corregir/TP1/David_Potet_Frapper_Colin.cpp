/*  auteur : David.Potet et Frapper Colin 
Role : affichage du nombre de jours dans le mois, d'une annÃ©e si elle est bissextile ou non et de la date du lendemain 
*/

#include <iostream>

using namespace std;

//-----------------------------------------------------------------


// Enregistrement t_date 
typedef struct t_date 
{
        int annee ;
        int mois ;
        int jour ;
};

// fonction principale

int main ()
{
        bool bissextile ;
        int nbJoursAnnee ;
        int nbJoursMois ;
        t_date D ;
        cout << "Saisir une annee" << endl ;
        cin >> D.annee ;
        cout << "Saisir un mois" << endl ;
        cin >> D.mois ;
        cout << "Saisir un jour"<< endl ;
        cin >> D.jour ;
        cout << "Vous avez choisi la date : " << D.jour << "/" << D.mois << "/" << D.annee << endl ;
   
        // Partie annee bisextile ou non
	if (D.annee % 4 == 0 )   
	{
		if (D.annee % 100 != 0 )
	        {
		        nbJoursAnnee  = 366 ;
		}
	        else if (D.annee % 400 == 0 ) 
		{   
		        nbJoursAnnee  = 366 ;
		}
		
	        else 
	        {
                        nbJoursAnnee  = 365 ;
                }
       }
       
        // Partie calcul du nombre de jours maximum du mois choisi 
        if (D.mois % 2 != 0 && D.mois < 8 )
        {
                nbJoursMois = 31 ;
        }
                else if (D.mois % 2 == 0 && D.mois > 7 )
                {
                         nbJoursMois = 31 ;
                }
                else if ( D.mois % 2 != 0 && D.mois > 7 )
                {
                         nbJoursMois = 30 ;
                }
                else  if ( D.mois % 2 == 0 && D.mois < 7 )
                {
                        nbJoursMois = 30 ;
                }
        
        // Affichage si annee est bisextile ou non selon son nombre de jours et test pour mois de fÃ©vrier 
        if ( nbJoursAnnee == 366  )
        {
              
                bissextile = true ;
                if ( D.mois == 2 )
                {
                        nbJoursMois = 29 ;
                }
                        
                
        }
        else 
         {
                bissextile = false ;
                if ( D.mois == 2 )
                {
                        nbJoursMois = 28;
                }
                        
                
        }
      
      // Partie pour la date du lendemain 
       if (D.jour == nbJoursMois )
       {
                 if (D.mois == 12 )
                 {
                        D.annee ++ ;
                        D.mois = 0 ;                       
                 }
         D.jour = 1 ;
         D.mois ++ ;
       }
       else 
       {
                D.jour ++ ;
       }
       
       if ( bissextile == true )
       {
        
                cout << "L'annÃ©e est bissextile et le nombre de jours du mois est " << nbJoursMois << " et la date du lendemain est : " << D.jour << "/" << D.mois << "/" << D.annee << endl ;
       }
       else if ( bissextile == false )
       {
                 cout << "L'annÃ©e est non bissextile et le nombre de jours du mois est  " << nbJoursMois << " et la date du lendemain est : " << D.jour << "/" << D.mois << "/" << D.annee << endl ;
       }
}




/*      Jeux d'essai

1er Jeu d'essai : 
        une annee : 2000 
        un mois : 12 
        un jour : 31 
        remarque : l'annee est bissextile 
        affichage : annee bissextile, nbJourMois : 31, la date du lendemain est : 01/01/2001
        
2Ã¨me Jeu d'essai :
        une annee : 1999
        un mois : 11 
        un jour : 24 
        affichage : annee non bissextile, nbJourMois : 30, la date du lendemain est : 24/11/1999
        
3Ã¨me Jeu d'essai :
        une annee 1996
        un mois : 02 
        un jour : 12
        affichage : annee bissextile, nbJourMois : 29, la date du lendemain est : 13/02/1996

4Ã¨me Jeu d'essai :
        une annee : 1901 
        un mois : 02 
        un jour : 28
        affichage : annee non bissextile, nbJourMois : 28, la date du lendemain est : 01/03/1901
*/
