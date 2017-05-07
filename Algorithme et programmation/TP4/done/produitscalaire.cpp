/* exo 578 et 579.cpp - auteur : A. GUEHO ; C. ROCHER 

Role : Calculer le produit scalaire de vecteur*/


#include <iostream>
#include <string>
using namespace std ;


//On définit un type vecteur avec un entier pour la dimension du vecteur 
//et un pointeur vers un tableau de réels pour les valeurs

struct t_vecteur
{
	int taille;
	float* ptab;
};


//On crée une fonction permettant de saisir la taille et les valeurs du vecteur

t_vecteur Saisie_Vecteur ()
{
	
	int i;
	t_vecteur v;
	float val;
	
//On effectue une saisie contrôlée pour la taille afin que l'utilisateur entre une valeur positive 

	do
	{
		cout<<"Saisir la taille du vecteur"<<endl;
		cin>>v.taille;
		}
	while (!(v.taille>0));
	
//Allocation d'un tableau de réels de même dimension que le vecteur
	
	v.ptab= new float [v.taille];
//On entre les valeurs

	for (i=0; i<=v.taille-1; i++) {
		cout<<"Saisir la "<<i+1<<"ième valeur"<<endl;
		cin>>val;
		v.ptab[i]=val;  // équivalent à(memoire(v.ptab))[i]=val
	}	
	return(v);
}

//On crée une fonction pour calculer le produit scalaire de 2 vecteurs

float Produit_Scalaire(t_vecteur v1, t_vecteur v2)
{
	int i;
        
//res permettra de stocker les valeurs pour la boucle de calcul (for)

	float res;
        
//On vérifie que les vecteurs ont la même dimension

	if (v1.taille == v2.taille){
		res=0;
                
//On crée une boucle qui traduit la formule du produit scalaire 
//(x*x'+y*y'...) grace aux données des tableaux des vecteurs

		for (i=0; i<=v1.taille-1;i++){
			res = res+v1.ptab[i]*v2.ptab[i];
		}
		cout<<"Le produit scalaire des deux vecteurs est "<<res<<endl; 
        return res;
	}
        
//On prend en compte le cas où les vecteurs ne sont pas de même 
//dimension : on ne peut calculer le produit scalaire

        else
        {
			cout<<"On ne peut calculer le produit scalaire car les vecteurs n'ont pas la même dimension"<<endl;
                return 0;
        }
}

//La fonction principe saisit 2 vecteurs puis calcule leur produit scalaire

int main()
{

	t_vecteur vect1, vect2;
	vect1=Saisie_Vecteur();
	vect2=Saisie_Vecteur();
	Produit_Scalaire(vect1,vect2);

	return(0);
}
	
/* Test de l'algorithme :
* Test n°1 : Deux vecteurs de même dimension v1 = (3,2,1) et v2=(2,3,1)
Saisir la taille du vecteur
3
Saisir la 1ième valeur
1
Saisir la 2ième valeur
2
Saisir la 3ième valeur
3
Saisir la taille du vecteur
3
Saisir la 1ième valeur
2
Saisir la 2ième valeur
3
Saisir la 3ième valeur
1
Le produit scalaire des deux vecteurs est 11
Test verifié




* Test n°2 On test avec des valeurs négatives pour la taille du vecteur
Saisir la taille du vecteur
-1
Saisir la taille du vecteur
0
Saisir la taille du vecteur
2
L'algorithme redemande à l'utilisateur de resaisir la valeur de la taille
Test vérifié

 
 

* Test n°3 : Deux vecteur de dimension differente v1=(0,1) et v2=(6)
Saisir la taille du vecteur
2
Saisir la 1ième valeur
0
Saisir la 2ième valeur
1
Saisir la taille du vecteur
1
Saisir la 1ième valeur
6
On ne peut calculer le produit scalaire car les vecteurs n'ont pas la même dimension
test verifié




* Test n°4 : on test avec des valeurs négative tel que 
* v1= (-9,0,17) et v2=(-22,-1,0)
Saisir la taille du vecteur
3
Saisir la 1ième valeur
-9
Saisir la 2ième valeur
0
Saisir la 3ième valeur
17
Saisir la taille du vecteur
3
Saisir la 1ième valeur
-22
Saisir la 2ième valeur
-1
Saisir la 3ième valeur
0
Le produit scalaire des deux vecteurs est 198
Test verifié


Test n°4 : on test avec des valeurs réelles tel que 

Saisir la taille du vecteur
2
Saisir la 1ième valeur
6.2
Saisir la 2ième valeur
1.58
Saisir la taille du vecteur
2
Saisir la 1ième valeur
4.123
Saisir la 2ième valeur
0.126
Le produit scalaire des deux vecteurs est 25.7617

*/
