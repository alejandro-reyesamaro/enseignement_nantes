#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h> 
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

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

sem_t mutex;

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
			sem_wait(&mutex);
			deers = deers + 15 * deers / 100;
			// printing population after reproduction		
			//printf("Reproduction: %d\n", deers);
			sem_post(&mutex);
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
			sem_wait(&mutex);
			deers = deers - 25;
			// printing population after hunting
			//printf("Hunting : %d\n", deers);
			sem_post(&mutex);
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
	sem_t mutex_deer;
	sem_t mutex_kill;
	sem_t mutex_attente;

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
	if (pthread_create(&thread_deer, NULL, code_thread_deer, (void *)NULL))
	{ 
			perror("pthread_create deers");
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

	// Waiting for threads
	pthread_join(thread_deer, NULL);
	pthread_join(thread_hunter, NULL);
	pthread_join(thread_inspector, NULL);

	int survivors = MAX(0,deers);
	printf("Survivors %d\n", survivors);
	
	return 0;
}

// TO COMPILE
// gcc thr_2017.c -lpthread -o thr_sleep