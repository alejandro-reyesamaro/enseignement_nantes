#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h> 
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

const int N = 12;
//int temp_repr[N] = {0,0,1,0,0,0,0,0,1,0,0,0};
//int temp_hunt[N] = {0,0,0,1,0,0,1,1,0,0,0,1};
int temp_repr[12] = {1,1,1,1,1,1,1,1,1,1,1,1};
int temp_hunt[12] = {1,1,1,1,1,1,1,1,1,1,1,1};

typedef struct {
	int N;				// partitions (12: months)
    int * repr_season;  // reproduction months (bit-flags)
    int * hunt_season;	// hunting months (bit-flags)
} t_rule;

// Declaration du semaphore d'exclusion mutuelle
sem_t mutex_reproduction, mutex_hunting, mutex_inspection;

// L'objet critique a proteger
int val=0;
//int day_light = 1;

int month = 0;
int year = 2006;

t_rule read_reproduction_seasons()
{
	t_rule s;
	s.N = 12;	
	s.repr_season = malloc(sizeof(int) * 12);
	s.hunt_season = malloc(sizeof(int) * 12);

	FILE *file = fopen("fseasons", "r");
	int i;
	char c;
	for(i = 0; i < 12; i++)
	{
		c = (char)fgetc(file);
		s.repr_season[i] = atoi(&c);
	}
	for(i = 0; i < 12; i++)
	{
		c = (char)fgetc(file);
		s.hunt_season[i] = atoi(&c);
	}
	return s;
}

void* code_thread_wolf(void *arg)
{	
	int i = 0;

	while(i < 20)
	{		
		sem_wait(&mutex_reproduction);
		if(val <= 0)
		{
			sem_post(&mutex_hunting);
			return NULL;		
		}
		if(temp_repr[month])
		{
			val = val + 15 * val / 100;			
			printf("Reproduction %d: %d\n", month, val);
		}
		sem_post(&mutex_hunting);
		
		i++;
	}
	return NULL;
}

void* code_thread_hunter(void *arg)
{	
	int i = 0;
	
	while (i < 20)
	{
		
		sem_wait(&mutex_hunting);
		if(temp_hunt[month])
		{
			val = val - 25;
			printf("Hunting : %d\n", val);
		}
		sem_post(&mutex_inspection);
		if(val <= 0)
			return NULL;

		i++;
	}	
	return NULL;
}

void* code_thread_inspector(void *arg)
{	
	int i;	
	for (i = 0; i < 20; i++)
	{
		sem_wait(&mutex_inspection);
		year = year + (month + 1) / 12;
		printf("Population on %d/%d: %d\n", (month+1), year, val);
		printf("----------\n");
		month = (month + 1) % 12;
		sem_post(&mutex_reproduction);
		if(val <= 0)
			return NULL;
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("sem : operande manquant\n");
		printf("Utilisation : ./sem valeur\n");
		exit(EXIT_FAILURE);
	}

	// Recuperation de la valeur lors du lancement du programme
	val = atoi(argv[1]);

	// Declaration du thread
	pthread_t thread_wolf, thread_hunter, thread_inspector;

	/* Initialisation du semaphore */
	sem_init(&mutex_reproduction, 0, 1);
	sem_init(&mutex_hunting, 0, 0);
	sem_init(&mutex_inspection, 0, 0);


	// Creation of 3 threads
	if (pthread_create(&thread_wolf, NULL, code_thread_wolf, (void *)NULL))
	{ 
			perror("pthread_create wolf");
			exit(EXIT_FAILURE);
	}	
	if (pthread_create(&thread_hunter, NULL, code_thread_hunter, (void *)NULL))
	{ 
			perror("pthread_create hunter");
			exit(EXIT_FAILURE);
	}
	if (pthread_create(&thread_inspector, NULL, code_thread_inspector, (void *)NULL))
	{ 
			perror("pthread_create inspector");
			exit(EXIT_FAILURE);
	}

	// Attente de la terminaison des threads
	pthread_join(thread_wolf, NULL);
	pthread_join(thread_hunter, NULL);
	pthread_join(thread_inspector, NULL);

	/* Destruction du semaphore */
	sem_destroy(&mutex_reproduction);
	sem_destroy(&mutex_hunting);
	sem_destroy(&mutex_inspection);

	int survivors = MAX(0,val);
	printf("Survivors %d\n", survivors);
	
	return 0;
}

// TO COMPILE
// gcc -g -Wall -pthread sem.c -lpthread -o sem.exe