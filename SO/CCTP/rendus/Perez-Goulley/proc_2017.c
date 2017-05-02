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

int main(int argc, char *argv[])
{
	pid_t pid; int status, waitsignal;
	seasons = read_seasons();
	print_seasons(seasons);
	int i;
	pid = fork();
	
	for(i = 0; i < seasons.N; i++){
		if(seasons.reproduction_seasons[i] == 0 && seasons.hunting_seasons[i]==0){
			printf("Nothing \n");
		}
		else if(seasons.reproduction_seasons[i] == 1 && seasons.hunting_seasons[i] == 1){
			if(pid == -1){
				perror("Impossible de créer le processus fils");
			}
			else if(pid == 0){
				printf("Reproduction and ");
				exit(0);
			}
			else{
				printf("Hunting \n");
				wait(&status);
			}
		}
		else if(seasons.reproduction_seasons[i] == 1){
			printf("Reproduction \n");
		}
		else if(seasons.hunting_seasons[i] == 1){			
			printf("Hunting \n");
		}
	}
		
	return 0;
}
// TO COMPILE
// gcc proc_2017.c -lpthread -o proc