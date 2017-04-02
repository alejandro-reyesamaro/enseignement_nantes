#include <iostream>
using namespace std;

bool Verification(int year);
int Nombrejours(int month, bool bissextile);
void Date(int & day, int nbJours_mois, int & month, int & year);


//fonction secondaire
bool Verification(int year)
{

	bool bissextile ;

	//determine si une année est bissextile
	if((year%4)==0){
		
		if((year%100)==0){
			
			if((year%400)==0){
				bissextile = true;
			}
			else{
				bissextile = false;
			}
		}
		else{
			bissextile = true;
		}
	}
	else{
		bissextile = false;
	}

	return bissextile;
}

//fonction secondaire

int Nombrejours(int month, bool bissextile)
{
	int nbJours_mois;
	if(month <= 7)
		{ if((month % 2) != 0)
			{	nbJours_mois = 31;
			}
	else 
		{
			if(month != 2)
				{ nbJours_mois = 30;
				}
		    else {
				if (bissextile == true)
					{nbJours_mois = 29;
				}
				else {
					nbJours_mois = 28;
				}
			}
		}
	}
	else { 
		if((month % 2) == 0)	
			{  nbJours_mois = 31;
			}
	      else { 
			nbJours_mois = 30;
		  }
	}
	return nbJours_mois;
 }

//fonction secondaire

void Date(int & day, int nbJours_mois, int  & month, int & year)
{
	
	if (day < nbJours_mois)
	{
		day ++;
	}
	else {
		day = 1;
		if (month < 12 )
		{
			month ++;
		}
		else {
			month = 1;
			year ++;
		}
	}
}
	

//fonction principale

int main()
{
	int year;
	int day;
	int month;
	int nbJours_mois;
	int nbJours_annee;
	bool bissextile = false;
	string date;

	cout << "Ecrire une année: " << endl;
	cin >> year;
	cout << "Ecrire un mois: " << endl;
	cin >> month;
	cout << "Ecrire un jour: " << endl;
	cin >> day;
	
	  

	bissextile = Verification(year);
	nbJours_mois = Nombrejours(month,bissextile);
	Date(day, nbJours_mois, month, year);

	//determine le noumbre de jours suivant si l'année est bissextile ou non
	if (bissextile == true){
		nbJours_annee = 366;
	}
	else{
		nbJours_annee = 365;
	}

	cout << "Cette année comporte "<< nbJours_annee << " jours."<<endl;
	cout << "Le nombre de jours dans le mois est " << nbJours_mois <<endl;
	cout << "Le lendemain est le " << day << " / " << month <<" / "<< year << endl;
	return(0);
}

/* TEST:
 * On a pris pour annee 1999, mois 12 et jour 31 
 * cela affiche annee comporte 365 jours, le mois contient 31 jours, le lendemain est 1/1/2000
 * On a pris pour annee 2000, mois 2 et jours 29
 * cela affiche annee comporte 366 jours , le mois contient 29 jours, le lendemain 1/3/2000
*/
