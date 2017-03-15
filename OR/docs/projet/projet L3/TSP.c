/* Un petit projet pour les L3 Informatique! */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h> // nous allons utiliser la bibliothèque de fonctions de GLPK 

#define SizeMax 150  // SizeMax : constante définissant la taille maximale d'instance considérée ici 


/* Déclarations pour le compteur de temps CPU */
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

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

/* Lecture des données (recuperation de la taille de l'instance puis de la matrice des couts)
   Au passage, il est testé si l'instance est symétrique  */
void lecture_data(char *file, int C[SizeMax][SizeMax], int *nSize, int *sym)
{
  int i,j;
  FILE *fin;

  int val;

  fin = fopen(file,"rt");
  
  fscanf(fin,"%d",&val);
  *nSize = val;

  /* C */
  for (i=0; i < *nSize; i++)
    for (j=0; j < *nSize; j++)
    {
      fscanf(fin,"%d",&val);
      C[i][j] = val;
    }

  /* Matrice symétrique? */    
  *sym = 1;
  i = 0;
  while((i < *nSize) && (*sym == 1))
  {
    j = i+1;
    while((j < *nSize) && (*sym == 1))
    {
      if (C[i][j] != C[j][i]) *sym = 0;
      j++;
    }
    i++;
  }
  fclose(fin);
}


/* Test d'appartenance d'un entier dans un tableau (utilisé pour la décomposition d'une permutation en cycles disjoints) */
int app(int *t,int taille,int n)
{
  int i = 0;
  while((i < taille)&&(t[i] != n)) i++;
  if ( i == taille) return 0;
  else      return 1;
}

/* Programme principal : contient la construction et la résolution des problèmes */
int main(int argc, char *argv[])
{
  int i,j;
  int C[SizeMax][SizeMax]; // matrice de coûts 
  int nSize; // taille du problème 
  int sym; // type d'instance, symétrique : 1, assymétrique : 0  
  int nbcreux,nbrows; // variable indiquant le nombre d'éléments non-creux de la matrice creuse et le nombre de contraintes à 1 près éventuellement (tableaux de GLPK commençant à 1...) 
  double z, x[SizeMax * SizeMax]; // variables récupérant les résultats de l'optimisation (fonction objectif et variables) par GLPK 
  int obj, X[SizeMax]; // Solution "propre" (entière) vue sous la forme d'une permutation 
  double temps; // temps CPU
  int nbsol = 0; int nbcontr = 0; // compteur du nombre de résolution, et du nombre de contraintes ajoutées 

  /* ensemble de variables traduisant la permutation sous forme d'un produit de cycles */
  int trouve,next; 
  int taillemincycle, indmincycle;
  int nbcycle, tailletabcycle;	
  int tabcycle[SizeMax];
  int begcycle[SizeMax];
  int taillecycle[SizeMax]; 

  /* structures de données propres à GLPK */
  glp_prob *prob; // déclaration d'un pointeur sur le problème
  int *ia, *ja;
  double *ar; // déclaration matrice creuse
  int tailleMatCreuse; 
	
  /* Quelques définitions de paramètres pour supprimer des affichages de GLPK dans lesquels on se noierait */
  glp_smcp parm;
  glp_init_smcp(&parm);
  parm.msg_lev = GLP_MSG_OFF;

  glp_iocp parmip;
  glp_init_iocp(&parmip);
  parmip.msg_lev = GLP_MSG_OFF;

  /* chargement des données */
  lecture_data(argv[1],C,&nSize,&sym); 
	
  /* GO! */
  crono_start(); 

  /* Allocation mémoire pour les structures de données propres à GLPK */
  tailleMatCreuse = 1 + 4 * nSize * nSize;
  ia = (int *) malloc (tailleMatCreuse * sizeof(int));
  ja = (int *) malloc (tailleMatCreuse * sizeof(int));
  ar = (double *) malloc (tailleMatCreuse * sizeof(double));  // On a besoin de 2 * nSize * nSize - 2 * nSize cases avant l'ajout des contraintes des sous-tours, on a donc un peu de marge avant de faire un realloc

  prob = glp_create_prob(); // allocation mémoire pour le problème  
  glp_set_prob_name(prob, "TSP"); // affectation d'un nom (on pourrait mettre NULL) 
  glp_set_obj_dir(prob, GLP_MIN); // Il s'agit d'un problème de minimisation 
	
  /* Définition des variables et contraintes du problème "initial" */
  nbrows = 2 * nSize; // nombre initial de contraintes 
  glp_add_rows(prob, nbrows); // Déclaration du nombre de lignes de la matrice de contraintes : 2*nSize 
  for(i=1;i<=2*nSize;i++)
  {
    glp_set_row_bnds(prob, i, GLP_FX, 1.0, 1.0); // Toutes les contraintes initiales sont du type "... = 1" 
  }	

  glp_add_cols(prob, nSize*nSize); // Déclaration du nombre de variables : nSize*nSize 
  for(i=1;i<=nSize*nSize;i++)
  {
    glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0); 
    glp_set_col_kind(prob, i, GLP_BV);	// les variables sont binaires 	
  } 

  /* Définition des coefficients des variables dans la fonction objectif */
  for(i = 0;i < nSize;i++)
    for(j = 0;j < nSize;j++)
    {
      glp_set_obj_coef(prob,i*nSize + j + 1,(double) C[i][j]);
    }

  /* Définition des coefficients non-nuls dans la matrice des contraintes */
  nbcreux = 1;
  for(i = 0;i < nSize;i++)
    for(j = 0;j < nSize;j++)
    {
      if (i != j) // On supprime immédiatement les variables x_{ii}, autre solution : pénaliser fortement les coûts correspondants 
      {
	ia[nbcreux] = i + 1; ja[nbcreux] = i*nSize + j + 1; ar[nbcreux] = 1.0; // La variable $x_{ij}$ intervient dans la ligne i ... 
	ia[nbcreux+1] = j + nSize + 1; ja[nbcreux+1] = i*nSize + j + 1; ar[nbcreux+1] = 1.0; // ...et la ligne j + nSize 
	nbcreux = nbcreux + 2;
      }
    }

  /* (Longue) boucle principale : résolution du problème, récupération de la solution	optimale, transformation en produits de cycle disjoints, ajout de contrainte(s) si nécessaire */
  nbcycle = 0;
  while (nbcycle != 1) 
  {
    glp_load_matrix(prob,nbcreux-1,ia,ja,ar); // chargement de la matrice dans le problème 
    glp_simplex(prob,&parm);	
    glp_intopt(prob,&parmip); // Résolution 
    nbsol++;
    z = glp_mip_obj_val(prob); // Récupération de la valeur optimale 

    /* Récupération de la valeur des variables et traduction en permutation à la volée */
    int trouve;
    for(i=0;i<nSize;i++) 
    {	
      trouve = 0;
      j = 0;
      while ((j < nSize) && (trouve == 0))
      {
	x[nSize*i + j] = glp_mip_col_val(prob,nSize * i + j + 1); 
	if (x[nSize*i + j] > 0.5)
	{
	  X[i] = j;
	  trouve = 1;  
	}
	j++;
      }
    } 
	
    /* calcul propre de la fonction objectif */
    obj = 0;
    for(i = 0;i < nSize;i++)
    {
      obj = obj + C[i][X[i]];	
    } 

    /* Décomposition en produit de cycles disjoints */	
    tailletabcycle = 0;
    nbcycle = 0;	
    while(tailletabcycle < nSize) // Tant que nous n'avons pas décomposé toute la permutation en cycles disjoints 
    {
      i = 0;
      while(app(tabcycle,tailletabcycle,i) == 1) i++; // On cherche une affectation qui n'appartient à aucun cycle encore défini 
      taillecycle[nbcycle] = 1;
      begcycle[nbcycle] = tailletabcycle;
      tabcycle[tailletabcycle++] = i; // Début d'un nouveau cycle 
      next = X[i];
      while(next != i) // Tant qu'on n'a pas bouclé, on continue d'avancer dans le cycle 
      {
	tabcycle[tailletabcycle++] = next;
	(taillecycle[nbcycle])++;
	next = X[next];
      }
      nbcycle++; // Cycle complété! 
    }
	
    /* Affichage de la décomposition en cycles disjoints */
    printf("obj = %d :",obj);
    for(i = 0;i < nbcycle;i++)
    {
      printf("( ");
      for(j = 0;j < taillecycle[i];j++) printf("%d ",tabcycle[begcycle[i]+j] + 1);
      printf(")");
    }
    puts("");		

    /* Si nous n'avons pas une solution admissible pour le TSP, nous allons déterminer le plus petit cycle et ajouter une ou deux contraintes (cas symétrique) au problème */
    taillemincycle = nSize;	
    if (nbcycle != 1) 
    {
      /* Détection du petit grand cycle pour le casser */
      for(i = 0;i < nbcycle;i++)
      {
	if (taillecycle[i] < taillemincycle)
	{
	  taillemincycle = taillecycle[i];
	  indmincycle = i;
	}
      }

      /* Ajout de la contrainte cassant ce cycle, 
	 réallocation mémoire des tableaux ia, ja et ar si nécessaire, 
	 affichage de la contrainte ajoutée à la volée */
      nbrows = glp_add_rows(prob,1);
      glp_set_row_bnds(prob, nbrows, GLP_UP, 0.0, taillemincycle - 1); /* Il d'agit d'une contrainte du type "... <= taillemincycle - 1" */
      printf("Ajout de la contrainte : ");nbcontr++;			
      for(i = begcycle[indmincycle];i < begcycle[indmincycle] + taillemincycle - 1;i++)
      {
	/* Parcours du cycle pour compléter la contrainte additionnelle */
	if (nbcreux >= tailleMatCreuse) 
	{
	  tailleMatCreuse += nSize * nSize;
	  ia = (int *) realloc (ia,tailleMatCreuse * sizeof(int));
	  ja = (int *) realloc (ja,tailleMatCreuse * sizeof(int));
	  ar = (double *) realloc (ar,tailleMatCreuse * sizeof(double));
	}
	ia[nbcreux] = nbrows;ja[nbcreux] = tabcycle[i] * nSize + tabcycle[i + 1] + 1;ar[nbcreux] = 1.0; 
	printf("+ x%d,%d ",tabcycle[i] + 1, tabcycle[i + 1] + 1);
	nbcreux++;
      }
      if (nbcreux >= tailleMatCreuse) 
      {
	tailleMatCreuse += nSize * nSize;
	ia = (int *) realloc (ia,tailleMatCreuse * sizeof(int));
	ja = (int *) realloc (ja,tailleMatCreuse * sizeof(int));
	ar = (double *) realloc (ar,tailleMatCreuse * sizeof(double));
      }
      ia[nbcreux] = nbrows;
      ja[nbcreux] = tabcycle[begcycle[indmincycle] + taillemincycle - 1] * nSize + tabcycle[begcycle[indmincycle]] + 1;
      ar[nbcreux] = 1.0; 
      printf("+ x%d,%d <= %d\n",tabcycle[begcycle[indmincycle] + taillemincycle - 1] + 1, tabcycle[begcycle[indmincycle]] + 1, taillemincycle - 1);
      nbcreux++;

      /* Ajout d'une 2e contrainte dans le cas symétrique pour un sous-tour de taille > 2 */
      if ((sym == 1) && (taillemincycle > 2))
      {
	nbrows = glp_add_rows(prob,1); 
	glp_set_row_bnds(prob, nbrows, GLP_UP, 0.0, taillemincycle - 1); // Il d'agit d'une contrainte du type "... <= taillemincycle - 1" 
	printf("Ajout de la contrainte : ");nbcontr++;			
	for(i = begcycle[indmincycle] + taillemincycle - 1;i > begcycle[indmincycle];i--)
	{
	  // Parcours du cycle et remplissage "à l'envers" pour obtenir correctement la contrainte 
	  if (nbcreux >= tailleMatCreuse) 
	  {
	    tailleMatCreuse += nSize * nSize;
	    ia = (int *) realloc (ia,tailleMatCreuse * sizeof(int));
	    ja = (int *) realloc (ja,tailleMatCreuse * sizeof(int));
	    ar = (double *) realloc (ar,tailleMatCreuse * sizeof(double));
	  }
	  ia[nbcreux] = nbrows; ja[nbcreux] = tabcycle[i] * nSize + tabcycle[i - 1] + 1;ar[nbcreux] = 1.0;
	  printf("+ x%d,%d ",tabcycle[i] + 1, tabcycle[i - 1] + 1);
	  nbcreux++;
	}
	if (nbcreux >= tailleMatCreuse) 
	{
	  tailleMatCreuse += nSize * nSize;
	  ia = (int *) realloc (ia,tailleMatCreuse * sizeof(int));
	  ja = (int *) realloc (ja,tailleMatCreuse * sizeof(int));
	  ar = (double *) realloc (ar,tailleMatCreuse * sizeof(double));
	}
	ia[nbcreux] = nbrows;
	ja[nbcreux] = tabcycle[begcycle[indmincycle]] * nSize + tabcycle[begcycle[indmincycle] + taillemincycle - 1] + 1;
	ar[nbcreux] = 1.0; 
	printf("+ x%d,%d <= %d\n",tabcycle[begcycle[indmincycle]] + 1, tabcycle[begcycle[indmincycle] + taillemincycle - 1] + 1, taillemincycle - 1);
	nbcreux++;
      }
    }
  } // Fin de la boucle while : enfin!


  /* Arrêt du chronomètre */
  crono_stop();
  temps = crono_ms()/1000,0;

  /* Affichage des résultats sous une forme lisible */
  printf("\n");
  puts("Résultat :");
  puts("-----------");
  printf("obj = %d : 1",obj);
  j = 0;
  for(i = 0;i < nSize;i++) 
  {
    printf(" -> %d",X[j] + 1);
    j = X[j];
  }
  puts("");
  printf("Temps : %f\n",temps);	
  printf("Nombre de résolutions : %d\n",nbsol);
  printf("Nombre de contraintes ajoutées : %d\n",nbcontr);

  /* Libération mémoire */
  free(ia);
  free(ja);
  free(ar);
  glp_delete_prob(prob); 
  return 0;
}

