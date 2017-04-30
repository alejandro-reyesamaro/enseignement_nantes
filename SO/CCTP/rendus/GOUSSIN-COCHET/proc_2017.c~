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
void handUSR1 ( int signo) {
printf ("reproduction") ;
signal(SIGUSR1, SIG_IGN); /* signal pris en compte une fois seulement */
}

/* code du handler pour le signal SIGUSR2 */
void handUSR2 ( int signo) {
printf ("hunting") ;

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
	signal (SIGUSR1, handUSR1) ;
	signal (SIGUSR2, handUSR2) ;
	int i =0;
	for(i = 0; i < seasons.N; i++)
	{
		if(seasons.reproduction_seasons[i] > seasons.hunting_seasons[i])
		{
			execlp("kill",getpid(),"SIGUSR2");
		}else{
			if(seasons.reproduction_seasons[i] < seasons.hunting_seasons[i])
			{
				execlp("kill",getpid(),"SIGUSR1");
			}else{
				if(seasons.reproduction_seasons[i] == seasons.hunting_seasons[i])
				{
					if(seasons.reproduction_seasons[i] == 0)
					{
						printf ("nothing\n") ;
					}else{
						execlp("kill",getpid(),"12");
						printf (" and ") ;
						execlp("kill",getpid(),"10");
					}
				}
			}
		}
	printf("\n");
	}
	seasons = read_seasons();
	print_seasons(seasons);
	while(1);
	return 0;
}

// TO COMPILE
// gcc proc_2017.c -lpthread -o proc
