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

void procHunt (int signo){
	signal(SIGUSR1, procHunt);
	printf("Hunting ");
}


void procReprod (int signo){
	signal(SIGUSR2, procReprod);
	printf("Reproduction ");
}
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
	for(i = 0; i < seasons.N; i++){
		printf("%d -> ",i+1);
		if(seasons.reproduction_seasons[i]+seasons.hunting_seasons[i]==2){
			printf("Reproduction and hunting");
		}
		else if(seasons.reproduction_seasons[i]+seasons.hunting_seasons[i]==0){
			printf("Nothing");
		}
		else{
			printf("Only ");
			if(seasons.reproduction_seasons[i]==1){
				printf("Reproduction");
			}
			else{
				printf("Hunting");
			}
		}
		printf("\n"); // reading "\n"
	}
	printf("\n");
	//signal(SIGUSR1,handINT1);
}

int main(int argc, char *argv[])
{
	seasons = read_seasons();
	print_seasons(seasons);
	
	return 0;
}


// TO COMPILE
// gcc proc_2017.c -lpthread -o proc