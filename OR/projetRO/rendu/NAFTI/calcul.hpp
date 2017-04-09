#include <list>

typedef struct{
  std::list<int> perm;
  int lon;
} regroupement;



typedef struct {
	int quantpuit; // Nombre de lieux
	int capaciteStockageDrone; 
	int *demande; // Demande de chaque puit
	int **C;
} donnees;


std::list< std::list<int> > regroupementP(int* requirement, int effectif, int stockage);

void regroupementP2(std::list<std::list<int> > &l, int* requirement, int effectif, int totalstockage, int cli, int stockage, std::list<int> lastList);

std::list<regroupement> echangerDeuxFois(std::list<std::list<int> > ec, const int** mat);
void echangeForce(regroupement &res, std::list<int> nouv, std::list<int> old, const int** mat);

int trouvve(const std::list<int> &l, const int** mat);

void resolution(const std::list<regroupement> &reg, const donnees &d);

void afficheListe(const std::list<int> &l);
void afficheListe(const std::list<regroupement> &l);
void afficheListeBis(const std::list< std::list<int> > &l);

