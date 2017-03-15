#include <iostream>

using namespace std;

int main(){

//Annee bissextile //Sebastien Le Breton et Camille Houlgatte

int annee;
int jours;
int mois;
int nbjours; // jours de l'année donnée
int joursmois; // nombre de jours du mois
int demainjours;
int demainmois;
int demainannee;

cout<< "saisir une annee"<< endl;
cin>>annee;

if (annee % 4 != 0){
                    nbjours=365;
                   }
else {
      if (annee % 100!= 0){
                           nbjours=366;
                          }
      else {
            if (annee % 400 == 0){
                                  nbjours=366;
                                 }
            else {
                  nbjours=365;
                 }
           }
     }

cout<< "Le nombre de jours de l'année est "<<nbjours<<endl ;

cout<< "saisir le numéro du mois"<< endl;
cin>> mois;
while (mois<1||mois>12){
                        cout<< "saisir le numéro du mois compris entre 1 et 12"<<endl;
                        cin>>mois;
                       }

cout<< "saisir un jour"<< endl;
cin>>jours;
if(mois == 2){
               if(nbjours==366){
                                 while(jours<1||jours>29){
                                                          cout<<"saisir un jour entre 1 et 29"<<endl;
                                                          cin>>jours;
                                                         }
                               }
               else {
                       while(jours<1||jours>28){
                                                cout<<"saisir un jour entre 1 et 28"<<endl;
                                                cin>>jours;
                                               }
                    }
             }
else
    {
     if(mois==4||mois==6||mois==9||mois==11) {
                                              while(jours<1||jours>30){
                                                                       cout<<"saisir un jour entre 1 et 30"<<endl;
                                                                       cin>>jours;
                                                                      }
                                             }
     else {
           while(jours<1||jours>31){
                                    cout<<"saisir un jour entre 1 et 31"<<endl;
                                    cin>>jours;
                                   }

          }
    }


if(mois == 2){
               if(nbjours==366){
                                 joursmois=29;
                               }
               else {
                       joursmois=28;
                    }
             }
else
      {
         if(mois==4||mois==6||mois==9||mois==11)
                 {
                    joursmois=30;
                 }
         else {
                 joursmois=31;

              }
      }

cout<< "le nombre de jours du mois est "<<joursmois<<endl;
demainjours = jours;
demainannee = annee;
demainmois = mois;

if(mois==2){
            if(jours==29||(jours==28 && nbjours==365)){
                                                       demainjours= 1;
                                                       demainmois=3;
                                                      }
            else{
                 demainjours=jours+1;
                }
          }
else {
      if (mois==4||mois==6||mois==9||mois==11){
                                               if (jours==30){
                                                              demainjours=1;
                                                              demainmois= mois+1;
                                                             }
                                               else {
                                                     demainjours=jours+1;
                                                    }
                                              }
      else {
            if (jours==31){
                           if (mois==12){
                                         demainjours=1;
                                         demainmois=1;
                                         demainannee= annee + 1;
                                        }
                           else {
                                 demainjours=1;
                                 demainmois= mois+1;
                                }
                          }
            else {
                  demainjours= jours+1;
                 }
          }
     }
cout<< "La date de demain est "<<demainjours<<"/"<<demainmois<<"/"<<demainannee<<endl;


return 0;
}
