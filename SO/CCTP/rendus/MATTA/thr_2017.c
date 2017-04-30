#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h> 
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/stat.h>


#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef struct {
	int N;							// seasons (12: months)
    int * reproduction_seasons;		// reproduction months (bit-flags)
    int * hunting_seasons;			// hunting seasons (bit-flags)
} t_park_seasons;

// Park rules declaration
t_park_seasons seasons;

// Critical object to protect (population of deers)
int deers = 0;

// Date time variables
int month = 0;
int year = 2006;

/// \function: testing_period
/// \abstract: the testing period
/// \input: -
/// \output: true if year 2010 is not arrived. false otherwise
int testing_period()
{
	return year < 2010; 
}

/// \function: read_seasons
/// \abstract: read the rules of the park from a text file called "fseasons"
/// \input: -
/// \output: t_park_seasons representing reproduction and hunting seasons
t_park_seasons read_seasons()
{
	t_park_seasons seasons;
	seasons.N = 12;
	seasons.reproduction_seasons 	= malloc(sizeof(int) * 12);
	seasons.hunting_seasons 		= malloc(sizeof(int) * 12);

	FILE * file = fopen("np_rules.txt", "r");
	int i;
	char c;
	for(i = 0; i < 12; i++)
	{
		c = (char)fgetc(file);
		seasons.reproduction_seasons[i] = atoi(&c);
	}
	c = (char)fgetc(file); // reading "\n"
	for(i = 0; i < 12; i++)
	{
		c = (char)fgetc(file);
		seasons.hunting_seasons[i] = atoi(&c);
	}
	return seasons;
}

/// \function: print_seasons
/// \abstract: print in console the content of a t_park_season object
/// \input: t_park_seasons representing reproduction and hunting seasons
/// \output: -
void print_seasons(t_park_seasons seasons)
{
	int i;
	for(i = 0; i < seasons.N; i++)
		printf("%d ", seasons.reproduction_seasons[i]);
	printf("\n");
	for(i = 0; i < seasons.N; i++)
		printf("%d ", seasons.hunting_seasons[i]);
	printf("\n");
}

/// \function: code_thread_deer
/// \abstract: code executed by the deer thread
/// \input: -
/// \output: NULL when deers become extinct
void * code_thread_deer(void * arg)
{
	while(deers > 0 && deers < 1000 && testing_period())
	{		
		if(seasons.reproduction_seasons[month])
		{
			deers = deers + 15 * deers / 100;
			// printing population after reproduction		
			//printf("Reproduction: %d\n", deers);
		}
		sleep(2);
	}
	return NULL;
}

/// \function: code_thread_hunter
/// \abstract: code executed by the hunter thread
/// \input: -
/// \output: NULL when deers become extinct
void * code_thread_hunter(void *arg)
{
	while (deers > 0 && deers < 1000 && testing_period())
	{
		sleep(1);
		if(seasons.hunting_seasons[month])
		{
			deers = deers - 25;
			// printing population after hunting
			//printf("Hunting : %d\n", deers);
		}
		sleep(1);
	}	
	return NULL;
}

/// \function: code_thread_inspector
/// \abstract: code executed by the inspector thread
/// \input: -
/// \output: NULL when deers become extinct
void * code_thread_inspector(void *arg)
{
	while (deers > 0 && deers < 1000 && testing_period())
	{
		sleep(2);
		printf("Population on %d/%d: %d\n", (month + 1), year, MAX(0,deers));
		year = year + (month + 1) / 12;
		month = (month + 1) % 12;
		//printf("----------\n");
	}
	return NULL;
}

int main(int argc, char *argv[])
{
    int pid;
    int i;

     /* Constante sur les sémaphores */
    struct sembuf
    operation_P = { 0, -1, 0 };
    struct sembuf
    operation_V = { 0, 1, 0 };
   

	if (argc < 2)
	{
		printf("thr_sleep : operand missing\n");
		printf("Using : ./thr_sleep value\n");
		exit(EXIT_FAILURE);
	}

	// Reading initial population from program params
	deers = atoi(argv[1]);

	seasons = read_seasons();
	//print_seasons(seasons);

	// Declaration du thread
	pthread_t thread_deer, thread_hunter, thread_inspector;


	// Creation of 3 threads
    thread_deer=semget(IPC_PRIVATE, 1, 0666);

	if (pthread_create(&thread_deer, NULL, code_thread_deer, (void *)NULL))
	{ 
			perror("pthread_create deers");
			exit(EXIT_FAILURE);
	}	
    
    semctl(thread_deer,0, SETVAL,1);/* Init( thread_deer, 1); */
    

    thread_hunter=semget(IPC_PRIVATE, 1, 0666);
	if (pthread_create(&thread_hunter, NULL, code_thread_hunter, (void *)NULL))
	{ 
			perror("pthread_create hunter");
			exit(EXIT_FAILURE);
	}
    semctl( thread_hunter, 0, SETVAL, 0); /* Init( thread_hunter, 1); */

    thread_inspector=semget(IPC_PRIVATE, 1, 0666);
	if (pthread_create(&thread_inspector, NULL, code_thread_inspector, (void *)NULL))
	{ 
			perror("pthread_create inspector");
			exit(EXIT_FAILURE);
	}
    semctl(thread_inspector,0, SETVAL,1);/* Init( thread_inspector, 1); */

	// Waiting for threads
	pthread_join(thread_deer, NULL);
	pthread_join(thread_hunter, NULL);
	pthread_join(thread_inspector, NULL);

	int survivors = MAX(0,deers);
	printf("Survivors %d\n", survivors);
    
    pid = fork();
    if (pid==0)
    {
        for (i=97; i<123; i++)
        {
            semop(thread_deer, &operation_P, 1); /* P(thread_deer) */
            printf("%c\n",i);
            semop(thread_hunter, &operation_V, 1); /* V(thread_hunter); */
            printf("%c\n",i);
            semop(thread_inspector, &operation_P, 1);/* P(thread_inspector); */

        }
    }
    else 
    {
        for (i=65; i<91; i++)
        {
            semop(thread_hunter, &operation_P, 1); /* P(thread_hunter); */
            printf("%c\n",i);
            semop(thread_deer, &operation_V, 1); /* V(thread_deer); */
             printf("%c\n",i);
            semop(thread_inspector, &operation_V, 1);/* V(thread_inspector); */
        }
    }
   
    /* On peut détruire les sémaphores */
    semctl(thread_deer, 0, IPC_RMID, 0);
    semctl(thread_hunter, 0, IPC_RMID, 0);
    semctl(thread_inspector, 0, IPC_RMID, 0);    

	return 0;
}

// TO COMPILE
// gcc thr_2017.c -lpthread -o thr_sleep
