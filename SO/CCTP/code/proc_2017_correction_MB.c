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

// Index for the sheep process 
int i_reproduction_season = 0;
// Index for the hunter process
int i_hunting_season = 0;

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

/// \abstract: signal to verify if the process must end 
void hand_SGL_test(int sgl) 
{
	printf("\n");
	if(i_hunting_season == 11)
		exit(0);
	else 
		i_hunting_season ++;
	signal (SIGUSR1, hand_SGL_test);
}

/// \abstract: signal to print the word "hunting"
void hand_SGL_print_and_test(int sgl) 
{
	printf("%d:hunting \n",getpid());
	if(i_hunting_season == 11)
		exit(0);
	else 
		i_hunting_season ++;
	signal (SIGUSR2, hand_SGL_print_and_test);
}

int main(int argc, char *argv[])
{
	seasons = read_seasons();
	print_seasons(seasons);
	setbuf(stdout,NULL);
	pid_t pid;
	if ( (pid = fork()) == -1 )
	{
		perror("Error forking"); 
		exit(1);
	}

	signal (SIGUSR1, hand_SGL_test);
	signal (SIGUSR2, hand_SGL_print_and_test);

	if (pid != 0)
	{ /* process 1 */
		//printf("parent:%d|child:%d\n", getppid(),getpid());
		while(1);
	}
	else
	{ /* process 0 */
		pid_t ppid = getppid();
		//printf("%d:PID PARENT\n",ppid);	
		int flag; 
		for(i_reproduction_season = 0; i_reproduction_season < 12; i_reproduction_season++)
		{
			flag = seasons.reproduction_seasons[i_reproduction_season] * 10 + seasons.hunting_seasons[i_reproduction_season];
			printf("%d -> ", i_reproduction_season + 1 );
			switch(flag)
			{
				case 0: 	// 0 - 0 : "Nothing"
					printf("%d:Nothing",getpid());
					kill(ppid, SIGUSR1);
				break;
				case 1: 	// 0 - 1 : "Only hunting"
					printf("%d:Only ",getpid());
					kill(ppid, SIGUSR2);
				break;
				case 10: 	// 1 - 0 : "Only reproduction"
					printf("%d:Only reproduction",getpid());
					kill(ppid, SIGUSR1);
				break;
				case 11: 	// 1 - 1 : "Reproduction and hunting"
					printf("%d:Reproduction and ",getpid());
					kill(ppid, SIGUSR2);
				break;
			}
			//sleep(1);
		}		
	}	
	
	return 0;
}

// TO COMPILE
// gcc proc_2017_correction.c -lpthread -o proc
/* Lo que veo yo como salida:
medusa@medusa-VirtualBox:~/X4I0010/cctp_2017.rar Folder$ ./proc_mb 
0 0 0 1 1 1 1 1 1 1 0 1 
1 0 1 0 1 1 1 1 1 1 1 0 
1 -> 14542:Only 14542:hunting 
2 -> 14542:Nothing
3 -> 14542:Only 14542:hunting 
4 -> 14542:Only reproduction
5 -> 14542:Reproduction and 14542:hunting 
6 -> 14542:Reproduction and 14542:hunting 
7 -> 14542:Reproduction and 14542:hunting 
8 -> 14542:Reproduction and 14542:hunting 
9 -> 14542:Reproduction and 14542:hunting 
10 -> 14542:Reproduction and 14542:hunting 
11 -> 14542:Only 14542:hunting 
12 -> 14542:Only reproduction

No veo que el child escriba su pid, ni que el escriba "hunting"
*/
