/*Wartel Amandine
Houbeaut Mélissandre
243L
*/

#include <iostream>
#using namespace std;



int main(){

// fontion est bissextile 

bool bissextile;
int annee;
int nbj;
int lendemain;
int jours;
int mois;


cout<< "Saisir une annee sous la forme aaaa";
cin >> annee;
cout<< "Saisir un mois en chiffre sous la forme mm";
cin>> mois;
cout<<"Saisir un jour sous la forme jj";
cin>> jour;

if (annee % 4 !=0)
   { 
      bissextile=false;
      cout<< (" Cette année n'est pas bissextile" );
   }
else 
   {
       if (annee % 100 == 0)
           {
              if (annee % 400=0 )
                  {    
                       bissextile=true;
                       cout << ("Cette annee est bissextile");
                  }
              else
                  {
                     bissextile= false;
                     cout<< ("Cette annee n'est pas bissextile");
                  }
       else
           {
              bissextile=true;
              cout<< ("Cette annee est bissextile");
           }
           }
     }

if(mois==2) 
          { 
             if(bissextile=true)
                 { 
               cout<<"Le mois comporte 29 jours"; 
               nbj=29;
                  }

           else
                 { 
                       cout<<"Le mois comporte 28jours";
                       nbj=28;
    }             }
if (mois==8)
           { 
              cout<<"Le mois comporte 31 jours";
              nbj=31;
              
            }

if((mois==1)||(mois==3)||(mois==5)||(mois==7)||(mois==9)||(mois==11)) 
            { cout<<"Le mois comporte 31 jours";
              nbj=31;
                               }


if ((mois==4)||(mois==6)||(mois==10)||(mois==12)) 
                   { cout<<"Le mois comporte 30 jours"; 
                     nbj=30;
}


if (nbj==31) {
                 if(jours==31) 
                          { lendemain=1; mois=mois+1;}
else {lendemain=jours+1;} }

if (nbj==30) {
                 if(jours==30) 
                          { lendemain=1; mois=mois+1;}
else {lendemain=jours+1;} }

if (nbj==29) {
                 if(jours==29) 
                          { lendemain=1; mois=mois+1;}
else {lendemain=jours+1;} }

if (nbj==28) {
                 if(jours==28) 
                          { lendemain=1; mois=mois+1;}
else {lendemain=jours+1;} }

if ((nbj!=31) && (nbj!=30)&& (nbj!=29) && (nbj!=28) { lendemain=jours+1; mois=mois;}

if (mois==12 && jours==31) { annee=annee+1}


cout<<"le lendemain est le :"lendemain"/" mois "/" annee;

































