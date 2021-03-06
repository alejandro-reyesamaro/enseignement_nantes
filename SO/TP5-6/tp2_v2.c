#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/* fork() duplicates the process, 
 * so after calling fork there are 
 * actually 2 instances of your program running.
 */
int main(void)
{ 
	pid_t pid;
	int i;
	if ( (pid = fork()) == -1 )
	{
		perror("fork"); 
		exit(1);
	}
	if (pid == 0)
	{ /* fils1 */
		for (i = 1; i <= 10; i++)
		{
			printf("%d\n", i);
			sleep(1);
		}
		return 0;
	}
	if (pid > 0)
	{ /* fils2 */
		for (i = 11; i <= 20; i++)
		{
			printf("%d\n", i);
			sleep(1);
		}
		return 0;
	}
	return 0;
}