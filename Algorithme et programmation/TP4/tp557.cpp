#include <iostream>
#include <fstream>


using namespace std;//L'algorithme a pour objectif de répondre au 5.7.8 et 5.7.9

struct vecteur{             //Type vecteur(coordonnées et taille)
	int nb;
	float *ptr;
};
void Detruire_vecteur(vecteur & V){
	delete [] V.ptr;
}

float Produit_scalaire(vecteur U,vecteur V){//Calcul du produit scalaire(si c'est possible)
	float res=0;
	int i;
	if(V.nb!=U.nb){
		cout<<"le produit scalaire ne peut être calculé"<<endl;//cas où le produit scalaire est impossible
		return res;
	} else {
		for(i=0;i<V.nb; i++){
			res += V.ptr[i]*U.ptr[i];//on ne peut pas retourner un réel
		}
		return res;//on retourne le résultat
	}
} 

int main() {
	
	float j;
	int nb=0;
	fstream flux;
	string source;
    vecteur U,V;
	
	
    source ="a.txt";
    
    flux.open(source.c_str(), ios::in);
    
    if (flux) {
		flux>>j;
		while (!(flux.eof())){
			nb++;
			flux>>j;
		}
		flux.close();
		flux.open(source.c_str(), ios::in);
		U.nb=nb;
		U.ptr = new float[nb];
		for(i=0;i<nb;i++){
			flux>>U.ptr[i];
		}
		flux.close();
		V=[
		
	}
		
return (0);		
}


/*Tests
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
