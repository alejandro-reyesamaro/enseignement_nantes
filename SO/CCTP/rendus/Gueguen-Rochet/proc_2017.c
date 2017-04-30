#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

typedef struct {
	int N;							// seasons (12: months)
    int * reproduction_seasons;		// reproduction months (bit-flags)
    int * hunting_seasons;			// hunting seasons (bit-flags)
} t_park_seasons;

// Park rules declaration
t_park_seasons seasons;

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
	c = (char)fgetc(file);
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
	printf("\n"); // reading "\n"
	for(i = 0; i < seasons.N; i++)
		printf("%d ", seasons.hunting_seasons[i]);
	printf("\n");
}



void print_fork(t_park_seasons seasons, int mois)
{
	
	int status;
	printf("%d -> ", mois+1 );
	
	int flag = seasons.reproduction_seasons[mois]+seasons.hunting_seasons[mois];

	if(flag == 0)
	{
		printf("Nothing \n");
	}

	if(flag == 1)
	{
		printf("Only ");
	}


	pid_t pid = fork();
	
	// reproduction
	if(pid != 0)
	{
		if(seasons.reproduction_seasons[mois] == 1)
		{
			printf("Reproduction");
		}
		if(flag == 1)
		{
			printf("\n");
		}
		if(flag == 2)
		{
			printf(" and ");
		}
		exit(0);
	}
	// hunting
	else
	{
		wait(&status);

		if(seasons.hunting_seasons[mois] == 1)
		{
			printf("hunting\n");
		}
	}
}

int main(int argc, char *argv[])
{
	int i;
	seasons = read_seasons();
	for(i = 0; i < seasons.N; i++)
	{
		print_fork(seasons,i);
	}
	
	
	return 0;
}
// TO COMPILE
// gcc proc_2017.c -lpthread -o proc