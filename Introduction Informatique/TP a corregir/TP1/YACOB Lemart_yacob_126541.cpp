/* YACOB Lemart
   Groupe: 243K
   11/février/2015
*/

#include <iostream>
using namespace std;

int main()
{
  int annee;

  cout << "Saisir une année ";      // année entrée par un user
  cin >> annee;
  if (annee % 400 == 0 || ((annee % 4 == 0) && (annee % 100 != 0)))   // si la année est bissextiles
    cout << "Il y aura 366 jours" << endl;
  else
    cout << "Il y aura 365 jours" << endl;

  int mois;     
  cout << "Saisir un mois ";    // Mois entrée par un unser 
  cin >> mois;

 if (mois == 4 || mois == 6 || mois == 9 || mois == 11)  // nombre de jour de mois choise par la user 
 cout << "nbJour = 30"<<endl;
else if (mois == 2)                                      // pour la mois 2  
{ 
	if(annee % 400 == 0 || ((annee % 4 == 0) && (annee % 100 != 0)))  
  		cout <<"nbJour = 29"<<endl;
	else  
  		cout <<"nbJour = 28"<<endl;
  
}
else  
 	cout << "nbJour = 31"<<endl;
}




/*   
 jeux d'essais


données            Resultat
Anée/ mois

2015/4		     365/30

2016/2		     366/29

1900/1		     365/31

2000/12		     366/31 */
