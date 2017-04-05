/*
 * Simple exemple d'utilisation des semaphores en C sous Linux.
 */


#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h> 
#include <pthread.h>

// Declaration du semaphore d'exclusion mutuelle
sem_t mutex;

// L'objet critique a proteger
int val=0; 

// Code monThread1
void* codeMonThread1(void *arg)
{
	int i;

	printf("Thread1 : l'objet critique n'est pas protege\n");	
	
	sem_wait(&mutex);  /* P(s); */
	printf("Thread1 : l'objet critique est protege, on peut l'utiliser. Sa valeur avant la boucle est %d\n", val);	
	for (i=0; i<10; i++)
		val=val*2;
	printf("Thread1 : l'objet critique est protege, on peut l'utiliser. Sa valeur apres la boucle est %d\n", val);	
	sem_post(&mutex); /* V(s); */

	printf("Thread1 : l'objet critique n'est plus protege\n");

	return NULL;
}

// Code monThread2
void* codeMonThread2(void *arg)
{
	int i;

	printf("Thread2 : l'objet critique n'est pas protege\n");	
	
	sem_wait(&mutex);  /* P(s); */
	printf("Thread2 : l'objet critique est protege, on peut l'utiliser. Sa valeur avant la boucle est %d\n", val);	
	for (i=0; i<10; i++)
		val=val+100;
	printf("Thread2 : l'objet critique est protege, on peut l'utiliser. Sa valeur apres la boucle est %d\n", val);	
	sem_post(&mutex); /* V(s); */

	printf("Thread2 : l'objet critique n'est plus protege\n");

	return NULL;
}


// Code du main()
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("sem : operande manquant\n");
		printf("Utilisation : ./sem valeur\n");
		exit(EXIT_FAILURE);
	}

	// Recuperation de la valeur lors du lancement du programme
	val=atoi(argv[1]);

	// Declaration du thread
	pthread_t monThread1, monThread2;

	/* Initialisation du semaphore */
	sem_init(&mutex, 0, 1);

	// Creation des 2 threads
	if (pthread_create(&monThread1, NULL, codeMonThread1, (void *)NULL))
		{ 
			perror("pthread_create 1"); 	
			exit(EXIT_FAILURE);
	}	
	if (pthread_create(&monThread2, NULL, codeMonThread2, (void *)NULL))
		{ 
			perror("pthread_create 2"); 	
			exit(EXIT_FAILURE);
	}

	// Attente de la terminaison des threads
	pthread_join(monThread1, NULL);
	pthread_join(monThread2, NULL);

	/* Destruction du semaphore */
	sem_destroy(&mutex);
	
	return 0;
}

// TO COMPILE
// gcc -g -Wall -pthread sem.c -lpthread -o sem.exe