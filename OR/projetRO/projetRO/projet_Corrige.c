/* Corrigé du projet VRP */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h> /* Bibliothèques utilisées pour mesurer le temps CPU */

#define MAXINT 100000

int pgtournee = 0;

/* Mesure du temps CPU */

struct timeval start_utime, stop_utime;

void crono_start()
{
	struct rusage rusage;
	
	getrusage(RUSAGE_SELF, &rusage);
	start_utime = rusage.ru_utime;
}

void crono_stop()
{
	struct rusage rusage;
	
	getrusage(RUSAGE_SELF, &rusage);
	stop_utime = rusage.ru_utime;
}

double crono_ms()
{
	return (stop_utime.tv_sec - start_utime.tv_sec) * 1000 +
    (stop_utime.tv_usec - start_utime.tv_usec) / 1000 ;
}

/* Structure contenant les données du problème */

typedef struct {
	int nblieux; /* Nombre de lieux (incluant le dépôt) */
	int capacite; /* Capacité du véhicule de livraison */
	int *demande; /* Demande de chaque client (la case 0 est inutilisée car le dépôt n'a aucune demande à voir satisfaire) */
	int **C; /* distancier (les lignes et colonnes 0 correspondent au dépôt) */
} donnees;

/* Structure contenant les combinaisons de villes qu'un camion peut livrer 
   (deux possibilités : la liste chaînée ou le tableau dynamique) 
    J'ai ici fait le choix d'une liste chaînée! */

typedef struct node {
	int nbclients; /* Nombre de clients de la combinaison */
	int *tabclients; /* Indices de ces clients */
	int *ordre; /* Ordre de visite de ces clients */
	int Ltour; /* Longueur de la plus petite tournée partant du lieu de production et desservant ces villes */
	struct node *suivant;
} listComb;


/* Fonctions pour ajouter un élément à la liste de combinaisons */

listComb * ajouterliste(int nb, int *tab,int *ord, int L,listComb * premier)
{
	listComb *p;
	p = (listComb *) malloc (sizeof (listComb));
	p->nbclients = nb;
	p->tabclients = tab;
	p->ordre = ord;
	p->Ltour = L;
	p->suivant = premier;
	return p;
}

/* Fonction de libération mémoire d'une liste de combinaisons */

listComb * supprimerliste(listComb *premier)
{
	listComb *precedent,*courant = premier;
	while(courant != NULL)
    {
		precedent = courant;
		courant = courant->suivant;
		free(precedent->tabclients);
		free(precedent->ordre);
		free(precedent);
    }
	return courant;
}

/* Fonction d'affichage d'une liste de combinaisons (pour vérification) */

void afficheliste(listComb *premier)
{
	int i;
	listComb *p = premier;
	while(p != NULL)
	{
		printf("liste des clients : "); 
		for(i = 0;i < (p->nbclients) - 1;i++) printf("%d,",p->tabclients[i]);
		printf("%d\n",p->tabclients[(p->nbclients) - 1]);
		printf("séquence de visite : "); 
		for(i = 0;i < (p->nbclients) - 1;i++) printf("%d,",p->ordre[i]);
		printf("%d\n",p->ordre[(p->nbclients) - 1]);
		printf("Longueur du tour : %d\n",p->Ltour);
		puts("\n");
		p = p->suivant;
	}
}

/* lecture des donnees (recuperation de la taille de l'instance puis de la matrice des couts) */

void lecture_data(char *file, donnees *p)
{
	int i,j;
	FILE *fin;
	
	int val;
	fin = fopen(file,"rt");
	
	/* Lecture du nombre de villes */
	
	fscanf(fin,"%d",&val);
	p->nblieux = val;

	/* Allocation mémoire pour la demande de chaque ville, et le distancier */
	
	p->demande = (int *) malloc (val * sizeof(int));
	p->C = (int **) malloc (val * sizeof(int *));
	for(i = 0;i < val;i++) p->C[i] = (int *) malloc (val * sizeof(int));
	
	/* Lecture de la capacité */
	
	fscanf(fin,"%d",&val);
	p->capacite = val;
	
	/* Lecture des demandes */
	
	for(i = 1;i < p->nblieux;i++)
	{
		fscanf(fin,"%d",&val);
		p->demande[i] = val;
	}
	
	/* Lecture du distancier */

	for(i = 0; i < p->nblieux; i++)
		for(j = 0; j < p->nblieux; j++)
		{
			fscanf(fin,"%d",&val);
			p->C[i][j] = val;
		}
		
	fclose(fin);
}

/* Fonction de libération mémoire des données */

void free_data(donnees *p)
{
	int i;
	for(i = 0;i < p->nblieux;i++) free(p->C[i]);
	free(p->C);
	free(p->demande);	
}

/* procédure récursive énumérant toutes les tournées possibles, en calculant au passage leur longeur,  
   et donnant en sortie la séquence la plus courte (paramètre *ord) et sa longueur (paramètre *L) */

void recTSP(donnees *p,int *tab,int taille,int *ordtemp,int tailletemp,int *ord, int *L, int k,int num)
{
	int i;
	int Ltemp;
	
	ordtemp[k] = tab[num]; num = num + 1;
	if (num == taille)
	{
		/* Détermination de la longueur de la tournée et MAJ éventuelle */
		Ltemp = p->C[0][ordtemp[0]];
		for(i = 0;i < taille - 1;i++) Ltemp += p->C[ordtemp[i]][ordtemp[i+1]];
		Ltemp += p->C[ordtemp[taille-1]][0];
		
		if (Ltemp < *L)
		{
			*L = Ltemp;
			for(i = 0;i < taille;i++) ord[i] = ordtemp[i];
		}
	}
	else for(i = 0;i < taille;i++) if (ordtemp[i] == 0) recTSP(p,tab,taille,ordtemp,tailletemp,ord,L,i,num);
	num = num - 1;ordtemp[k] = 0;	
}

/* Procédure résolvant le TSP par énumération totale (contenant l'allocation mémoire pour la permutation et l'appel initial */

void enumTSP(donnees *p,int *tab,int taille,int *ord,int *L)
{
	int i;
	int *ordtemp; /* séquence actuellement énumérée */
	int Ltemp; /* longueur du tour en construction */
	int tailletemp = 0;
	ordtemp = (int *) malloc (taille * sizeof(int));
	for(i = 0;i < taille;i++) ordtemp[i] = 0; /* permutation initialement vide */
	*L = MAXINT; /* aucune tournée encore énumérée */ 
	for(i = 0;i < taille;i++) recTSP(p,tab,taille,ordtemp,tailletemp,ord,L,i,0); /* énumération récursive */
	free(ordtemp);
}


/* Fonction récursive de construction des combinaisons de villes */

listComb *recComb(donnees *p, int k, int *tab, int tailletab, int total, listComb *liste,int *nbvar,int *taillecreux)
{
	int i,j;
	int *newtab;
	int *ord;
	int newtaille = tailletab + 1;
	int newtotal;
	int L;
	
	for(i = k;i < p->nblieux;i++)
	{
		newtotal = total + p->demande[i];
		if (newtotal <= p->capacite) /* Création d'une nouvelle combinaison */
		{
			/* indices des villes de la combinaison */
			newtab = (int *) malloc (newtaille * sizeof(int));
			for(j = 0;j < tailletab;j++) newtab[j] = tab[j];
			newtab[tailletab] = i;
			tab[tailletab] = i;
				
			/* tournée la plus courte et sa longueur (en partant du dépôt indicé 0) */
			ord = (int *) malloc (newtaille * sizeof(int)); 
			enumTSP(p,newtab,newtaille,ord,&L);
				
			/* ajout de la combinaison dans la liste */
			liste = ajouterliste(newtaille,newtab,ord,L,liste);
			(*nbvar)++;
			(*taillecreux) += newtaille;
			if (newtaille > pgtournee) pgtournee = newtaille;
			
			/* appel récursif */
			liste = recComb(p,i + 1,tab,newtaille,newtotal,liste,nbvar,taillecreux);
		}
	}
	return liste;
}

/* Fonction lançant la construction récursive des combinaisons de villes (qui définiront les variables du problème) */

listComb *enumComb(donnees *p,listComb *liste,int *nbvar,int *taillecreux)
{
	int *tab; /* Tableau définissant la combinaison en construction */
	int tailletab = 0; /* taille de ce tableau (initialement vide) */
	int total = 0; /* Demande de l'ensemble des villes de la combinaison en construction */
	
	tab = (int *) malloc (p->nblieux * sizeof(int));
	
	liste = recComb(p,1,tab,tailletab,total,liste,nbvar,taillecreux);
	
	free(tab);
	
	return liste;
}

int main(int argc, char *argv[])
{	
	/* Données du problème */

	donnees p; 
	
	/* structures de données propres à GLPK */
	
	glp_prob *prob;
	int *ia;
	int *ja;
	double *ar; // déclaration des 3 tableaux servant à définir la matrice "creuse" des contraintes
	
    /* variables récupérant les résultats de la résolution du problème (fonction objectif et valeur des variables) */
	
	double z; 
	double *x; 
	
	/* autres déclarations */ 

	int i,j,k;
	int nbvar = 0;
	int taillecreux = 0;
	int pos;
	
	/* Chargement des données à partir d'un fichier */
	
	lecture_data(argv[1],&p);

	crono_start(); // GO!

	listComb *liste;
	listComb *parcours;
	liste = enumComb(&p,liste,&nbvar,&taillecreux);
	
	//afficheliste(liste);
	
	/* Génération du problème de set partitionning */
		
	prob = glp_create_prob(); /* allocation mémoire pour le problème */ 
	glp_set_prob_name(prob, "Blade Runner"); /* affectation d'un nom */
	glp_set_obj_dir(prob, GLP_MIN); /* Il s'agit d'un problème de minimisation */
	
	/* Déclaration du nombre de contraintes (nombre de lignes de la matrice des contraintes) : (p->nbvilles) - 1 */
	
	glp_add_rows(prob, (p.nblieux) - 1); 
	
	/* Bornes sur les contraintes (toutes égales à 1) */
	
	for(i = 1;i <= (p.nblieux) - 1;i++) glp_set_row_bnds(prob, i, GLP_FX, 1.0, 1.0);
	
	/* Déclaration du nombre de variables : nbvar */
	
	glp_add_cols(prob, nbvar); 
	
	/* Toutes les variables sont binaires */
	
	for(i = 1;i <= nbvar;i++)
	{		
		glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0); 
		glp_set_col_kind(prob, i, GLP_BV);		
	} 
	
	/* Etant donné mon choix de structure de données (liste pour l'énumération des combinaisons de villes),
	   je remplis le problème par colonne (en particulier le fonction objectif et les contraintes simultanément */
	
	ia = (int *) malloc ((1 + taillecreux) * sizeof(int));
	ja = (int *) malloc ((1 + taillecreux) * sizeof(int));
	ar = (double *) malloc ((1 + taillecreux) * sizeof(double)); 
	
	pos = 1;
	parcours = liste;
	for(i = 1;i <= nbvar;i++)
	{
		glp_set_obj_coef(prob,i,parcours->Ltour);
		for(j = 0;j < parcours->nbclients;j++)
		{
			ia[pos] = parcours->tabclients[j];ja[pos] = i;ar[pos] = 1.0;pos++;
		}
		parcours = parcours->suivant;
	}
		
	/* chargement de la matrice dans le problème */
	
	glp_load_matrix(prob,taillecreux,ia,ja,ar); 
	
	/* optionnel : écriture de la modélisation dans un fichier (TRES utile pour debugger!) */
	
	glp_write_lp(prob,NULL,"blade.lp");
	
	/* Résolution, puis lecture des résultats */
	
	glp_simplex(prob,NULL);	glp_intopt(prob,NULL); /* Résolution */

	/* Problème résolu, arrêt du chrono */
	
	double temps;
	crono_stop();
	temps = crono_ms()/1000,0;
	
	/* Affichage des résultats */
	
	z = glp_mip_obj_val(prob); /* Récupération de la valeur optimale */
	x = (double *) malloc (nbvar * sizeof(double));
	for(i = 0;i < nbvar; i++) x[i] = glp_mip_col_val(prob,i+1); /* Récupération de la valeur des variables */
	
	printf("Nombre de variables = %d\n",nbvar);
	printf("Plus grande tournee = %d\n",pgtournee);
	printf("Distance totale = %lf\n",z);
	parcours = liste;
	for(i = 0;i < nbvar;i++)	
	{
		if (x[i] > 0.5) 
		{
			printf("tournée %d : [",j); 
			for(k = 0;k < (parcours->nbclients) - 1;k++) printf("%d,",parcours->ordre[k]);
			printf("%d] avec une longueur de %d\n",parcours->ordre[(parcours->nbclients) - 1],parcours->Ltour);
			j++;
		}
		parcours = parcours->suivant;
	} /* Affichage lisible de l'ensemble */
	
	printf("Temps : %f\n",temps);	
	
	/* libération mémoire */

	glp_delete_prob(prob); 
	liste = supprimerliste(liste);
	free_data(&p);
	free(x);
	free(ia);
	free(ja);
	free(ar);
	
	/* J'adore qu'un plan se déroule sans accroc! */
	return 0;
}
