#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
	int i=0;
	int pidfils = fork();
	if(pidfils != 0)
	{
		sleep(10);
		kill(pidfils, SIGKILL);
	} else
	{
		while(1) {
			sleep(1); 
			i++;
			printf("%d \n",i);
		}
	}
}