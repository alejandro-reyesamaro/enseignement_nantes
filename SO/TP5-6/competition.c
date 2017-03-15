#include <unistd.h> /* necessaire pour les fonctions exec */
#include <sys/types.h> /* necessaire pour la fonction fork */
#include <unistd.h> /* necessaire pour la fonction fork */
#include <stdio.h> /* necessaire pour la fonction perror */

int main(int argc, char * argv[]) {
	pid_t pid1,pid2,pid_premier;
	int status;
	switch(pid1 = fork()) 
	{
		case -1:
			perror("fork error");
		break;
		case 0:
			execlp("ls","ls",(char *) 0);
		break;
		default:
			switch(pid2 = fork()) {
				case -1:
					perror("fork error");
				break;
				case 0:
					execlp("ps","ps",(char *) 0);
					break;
				default:
				break;
			}
		break;
	}
	pid_premier = wait(&status);
	wait(&status);
	if (pid_premier == pid1)
	{
		printf("Premier processus a finir : %d\n", pid1);
	}
	else
	{
		printf("Premier processus a finir : %d\n", pid2);
	}
	return 0;
}