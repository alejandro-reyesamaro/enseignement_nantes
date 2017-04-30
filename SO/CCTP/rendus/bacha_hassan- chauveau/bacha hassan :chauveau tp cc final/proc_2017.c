#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

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

int main(int argc, char *argv[])
{
	seasons = read_seasons();
	print_seasons(seasons);
	
	pid_t pidA, pidB;
	int j = 0;
	pidA = fork();
	pidB = fork();

	
	for (int i = 0; i < 12; ++i)
	{

		if (pidB  == -1)
		{ 
			perror("fork"); exit(1);
		}

		if (pidB == 0)
		{ 
	 		if(seasons.reproduction_seasons[i] == 0 &&  seasons.hunting_seasons[j] == 1)
		 		printf("%d %s %s\n",i+1," -> ", "Only hunting");

		}

		

		if (pidA == 0)
		{ 
		 	if(seasons.reproduction_seasons[i] == 0 &&  seasons.hunting_seasons[j] == 0)
		 		printf("%d %s %s\n",i+1," -> ", "nothing");
		 	else if(seasons.reproduction_seasons[i] == 1 &&  seasons.hunting_seasons[j] == 0)
		 		printf("%d %s %s\n",i+1," -> ", "Only reproduction");
		 
		}
		//sleep(2);

		

		if(seasons.reproduction_seasons[i] == 1 &&  seasons.hunting_seasons[j] == 1)
		 		printf("%d %s %s\n",i+1," -> ", "reproduction and hunting");

		 j++;
	}
	 
	




	

	return 0;
}

// TO COMPILE
// gcc proc_2017.c -lpthread -o proc