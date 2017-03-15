//ANDRIAMISEZA Sanjy et JEHANNO Clement
#include<iostream>
using namespace std;

//Année bissextile
//------------------------------------------------------------

// Enregistrement de type "date"

struct date{
	int jour;
	int mois;
	int an;
	};

// Fonction année bissextile 
int est_bissextile(int an)	
	{
		if((an%4==0)&&(an%100!=0))
		{
			return true;
		}
		else
		{
			if(an%400==0)
			{
			return true;
			}
		  else 
			{
			return false;
			}
		}
	}

// Fonction nbdejours dans le mois
//------------------------------------------------------------------------------------
int jour(int moisFCT, int anFCT) {
	int nbjours;
	if (moisFCT!=02)
	{
		if( (moisFCT <= 7) && (moisFCT%2==1) ) 
		{																								//si num de mois impair jusqu'à 7
			return nbjours=31;
		}
		else if( (moisFCT >= 8) && (moisFCT%2==0) ) 
		{																							//si num de mois est pair de 8 à 12
			return nbjours=31;
		}
	// Note : on aurait pu mettre une condition de type "nbjour = 31" SI nos deux  conditions collées avec un "ou" ça aurait évité la redondance
		else if( (moisFCT < 7) && (moisFCT%2==0) )
		{
			return nbjours=30;
		}
		else if( (moisFCT> 7) && (moisFCT%2==1) )
		{
			return nbjours=30;
		}
	}

	if (moisFCT==02)
	{
		if(est_bissextile(anFCT))
		{return  nbjours=29; }
		else
		{return  nbjours=28; }
	}

}



	//------ ALGO
int main()
{
	//variables
	//-----------------------------------------------------
	int res,nbjours;
	int lendemain;
	bool estB;
	date JMA;

	cout << "Saississez le jour" << endl;
	cin >> JMA.jour;
	cout << "Saississez le mois" << endl;
	cin >> JMA.mois;
	cout << "Saississez l'année." << endl;
	cin >> JMA.an;
	

	//ALGO vérification si bissextile
	//---------------------------------------------------------------
	estB=est_bissextile(JMA.an);
	if (estB)
	{
		cout <<"Votre année est bissextile." << endl ;
		
	}
	else
	{
		cout <<"Votre année n'est pas bissextile." << endl ;
	}

	//ALGO nombre de jours dans un mois
	//-----------------------------------------------------------------------
	nbjours=jour(JMA.mois, JMA.an);
	cout <<"Votre mois comporte: " << nbjours << " jours."<< endl ;

	//ALGO la date du lendemain
	//-----------------------------------------------------------------------
	if((JMA.jour==28)&&(estB))
	{	cout << "Le lendemain sera 29 février " << JMA.an << endl; }
	if((JMA.jour==28)&&(!estB))
	{	cout << "Le lendemain sera 1 mars " << JMA.an << endl; }
/*	if((JMA.jour==30)&&(jour(JMA.mois, JMA.an)==30)
	{	cout << "Le lendemain sera 1 /" << JMA.mois + 1 << "/" << JMA.an << endl;}
 	if((JMA.jour==31)&&(jour(JMA.mois, JMA.an)==31)
	{	cout << "Le lendemain sera 1 /" << JMA.mois + 1 << "/" << JMA.an << endl;}
	
*/
}


/* JEUX D'ESSAIS

Pour l'année : On teste avec 2015 résultat attendu : 365
																	2016  résultat attendu : 366
																	1900  résultat attendu : 365
																	 2000 résultat attendu : 366
mois on teste avec 02
*/

