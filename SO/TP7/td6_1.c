#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 

void *ma_fonction_thread(void *arg) 
{ 
	int nbsec = (int)(arg); 
	printf("Je suis un thread et j'attends %d secondes\n", nbsec); 
	sleep(nbsec); 
	printf("Je suis un thread et je me termine"); 
	pthread_exit(NULL); 
} 

int main(void) 
{ 
	int ret; 
	pthread_t my_thread; 
	int nbsec=5; 
 
	/* on crée le thread */ 
	ret = pthread_create(&my_thread, NULL, ma_fonction_thread, (void *)nbsec); 
	if (ret != 0) 
	{ 
		fprintf(stderr, "Erreur de création du thread"); 
		exit (1); 
	} 
	pthread_join(my_thread, NULL); /* on attend la fin du thread */ 
	return 0; 
}