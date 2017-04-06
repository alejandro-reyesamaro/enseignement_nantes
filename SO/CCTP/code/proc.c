#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{ 
	pid_t pid;
	int i = 10;
	if ( (pid = fork()) == -1 )
	{
		perror("fork"); 
		exit(1);
	}

	if (pid == 0)
	{ /* fils1 */
		i = i + 10;
		printf("PID 0 : %d\n", i);
		return 0;
	}
	else
	{ /* fils2 */
		sleep(2);
		i = i + 10;
		printf("PID 0 : %d\n", i);
		return 0;		
	}
	return 0;
}