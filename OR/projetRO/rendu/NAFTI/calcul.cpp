#include "calcul.hpp"
#include <iostream>
#include <glpk.h>

using namespace std;

list< list<int> > regroupementP(int* requirement, int effectif, int stockage) {
	int maximum = 0;
	static list< list<int> > l;
	list<int> rien;
	for (int i = 1; i <= effectif -1; ++i) {
		maximum += requirement[i];
	}
	if (maximum <= stockage){
		for (int i = 1; i <= effectif - 1; ++i){
			rien.push_back(i);
		}
		l.push_back(rien); 
	}
	else{
		for (int i = 1; i <= effectif -1; ++i) {
			regroupementP2(l, requirement, effectif, stockage, i, 0, rien);
		}
	}
	return l;
}

void regroupementP2 (list< list<int> > &l, int* requirement, int effectif, int totalstockage, int pe, int stockage, list<int> lastList) {
	if ( pe <= effectif - 1) {
		if (  totalstockage >= requirement[pe]+stockage) 
		{ 
			lastList.push_back(pe);
			l.push_back(lastList);
			for (int j = pe+1; j <= effectif; ++j) {
				regroupementP2(l, requirement, effectif, totalstockage, j, stockage+requirement[pe], lastList);
			}
		}
	}
}

list<regroupement> echangerDeuxFois(list<  list<int> > a, const int** matrix){
	static list<regroupement> res;
	for (list< list<int>  >::iterator it = a.begin(); it != a.end(); it++){
		regroupement tmp;
		tmp.perm = *it;
		tmp.lon = trouvve(*it, matrix);
		list<int> rien;
		echangeForce(tmp, rien, *it, matrix);
		res.push_back(tmp);
	}
	return res;
}

void echangeForce(regroupement &res, list<int> nouv, list<int> old, const int** mat){
	if (old.size() == 0){
		int tmp = trouvve(nouv, mat);
		if (tmp < res.lon) 
		{
			res.lon = tmp;
			res.perm = nouv;
		}
	}
	else{
		list<int>::iterator it = old.begin();
		while ( it != old.end())
		{
			list<int> tmp1 (nouv);
			tmp1.push_back(*it);
			list<int> tmp2;
			list<int> tmp3;
			tmp2.assign(old.begin(), it);
			tmp3.assign(++it, old.end());
			tmp2.splice(tmp2.end(), tmp3);
			echangeForce(res, tmp1, tmp2, mat);
		}
	}
}

int trouvve(const list<int> &l, const int** mat){
	list<int>::const_iterator it = l.begin();
	int res = mat[0][*it];
	for (it = ++it; it != l.end(); ++it){
		res += mat[*--it][*++it];
	}
	res += mat[*--it][0];
	return res;
}

void resolution(const list<regroupement> &reg, const donnees &d) {
	glp_prob *prob;
	double z;

	int *ia,*ja;
	double *ar;
	ia = new int[reg.size()*d.quantpuit];
	ja = new int[reg.size()*d.quantpuit];
	ar = new double[reg.size()*d.quantpuit];

	cout << "/*" << endl;
	prob = glp_create_prob();
	glp_set_prob_name(prob, "Choix des regroupement");
	glp_set_obj_dir(prob, GLP_MIN);

	glp_add_rows(prob, d.quantpuit-1);

	for (int i = 1; i < d.quantpuit; ++i) { 
		glp_set_row_name(prob,i,"visite du puit "+i);
		glp_set_row_bnds(prob,i, GLP_FX, 1.0,1.0);
	}

	glp_add_cols(prob, reg.size());
	for (int i = 1; i <= reg.size(); ++i) {
		glp_set_col_kind(prob,i,GLP_BV); 
	}

	{
		int id = 1;
		for (list<regroupement>::const_iterator it = reg.begin(); it != reg.end(); ++it) {
			glp_set_obj_coef(prob, id, it->lon);
			++id;
		}
	}

	int nbCreux = 0; int numReg = 1;
	for (list<regroupement>::const_iterator it = reg.begin(); it != reg.end(); ++it) {
		for (list<int>::const_iterator itCli = it->perm.begin(); itCli != it->perm.end(); ++itCli) {
			++nbCreux;
			ia[nbCreux] = *itCli; ja[nbCreux] = numReg; ar[nbCreux] = 1.0;
		}
		++numReg;
	}
	glp_load_matrix(prob,nbCreux,ia,ja,ar);

	// definition des contraintes 

	glp_simplex(prob,NULL); glp_intopt(prob,NULL); 

	cout << "*/" <<endl<<endl;

	z = glp_mip_obj_val(prob);

	list<regroupement>::const_iterator it = reg.begin();
	for (int i = 0; i < reg.size(); ++i) {
		if (glp_mip_col_val(prob,i+1)) {
			cout << "x"<<i+1<<"=1 : ";
			afficheListe(it->perm);
			cout << endl;
		}
		++it;
	}

	glp_delete_prob(prob);

	cout << "z = " << (int)z << endl;

	delete[] ia;
	delete[] ja;
	delete[] ar;
}

void afficheListe(const list<int> &l) {
	cout << "{ ";
	for (list<int>::const_iterator it = l.begin(); it != l.end(); ++it) {
		cout << *it << " ";
	}
	cout << "} ";
}

void afficheListe(const list<regroupement> &l) {
	for (std::list<regroupement>::const_iterator it=l.begin(); it != l.end(); ++it) {
		cout << it->lon << " : ";
		afficheListe(it->perm);
		cout << endl;
	}
}

void afficheListeBis(const std::list< std::list<int> > &l) {
	cout << "{ "<< endl;
	for (list< list< int > >::const_iterator it = l.begin(); it != l.end() ; ++it) {
		cout << "{ ";
		for (list<int>::const_iterator it2 = it->begin(); it2 != it->end(); ++it2) {
			cout << *it2 << ' ' ;
		}
		cout << "} "<< endl;
	}

	cout << "} " << endl << endl;
}

