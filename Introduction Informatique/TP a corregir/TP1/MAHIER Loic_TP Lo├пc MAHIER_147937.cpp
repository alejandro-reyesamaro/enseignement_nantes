/* Affiche si l'année saisie par l'utilisateur est bissextile ou non,  indique le nombre de jours présent le mois saisie et la date du lendemain */
/* Loïc MAHIER   243k */

#include <iostream>

using namespace std;


// procédures

void bissextile(int annee, bool & b){ // fonction qui indique si l'annee est bissextile

    if((annee % 4==0 && annee % 100!=0)||(annee % 400==0))
    {
        cout << annee << " est une annee bissextile." << endl;
        b=true;
    }
    else
    {
        cout << annee << " n' est pas une annee bissextile" << endl;
        b=false;
    }

}


void nbJours(int mois, bool b, int & nbjours){ // indique le nombre de jours ce mois-ci

    if((mois >= 1 && mois <= 7 && (mois % 2 != 0)) || (mois >= 8 && (mois % 2 == 0))){

	nbjours = 31;
    	
    }
    else if(mois==2 && b)
    {

	nbjours = 29;
    	
    }
    else if(mois==2 && !b){

	nbjours = 28;
    	
    }
    else
    {

	nbjours = 30;
    	    
    }

    cout << "il y a " << nbjours << " jours ce mois-ci" << endl;

}

void joursLendemain(int & jours, int & mois, int & annee, int nbjours){ // indique la date du lendemain

    if((mois >= 1 && mois <= 7) || (mois >= 8 && mois % 2 == 0)){

    	if(jours<nbjours){
	
		jours += 1;
	
	}
	else if(jours==nbjours && mois==12){

		jours=1; mois=1; annee+=1;	

	}
        else{

		jours=1; mois=1;

	}
    }
    else if(mois==2){

	if(jours<nbjours){
	
		jours += 1;

	}
        else
	{

		jours=1; mois=1;

	}
    }
    else {

	if(jours<nbjours){

		jours += 1;

	}
	else
	{

		jours=1; mois=1;

	}
    } 
    
    cout << "Le lendemain sera le " << jours << '/' << mois << '/' << annee << endl;

}

// fonction principale

int main()
{
    int annee, mois, jours, nbjours;
    bool b;
    
    cout << "Saisissez une annee." << endl;
    cin >> annee;
    cout << "Saisissez un mois." << endl;
    cin >> mois;
    cout << "Saisissez un jours." << endl;
    cin >> jours;

    bissextile(annee,b);	
    nbJours(mois, b, nbjours);
    joursLendemain(jours, mois, annee, nbjours);

    return 0;
}


