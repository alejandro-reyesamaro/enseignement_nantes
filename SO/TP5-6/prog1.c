#include <unistd.h> /* necessaire pour les fonctions exec */
#include <sys/types.h> /* necessaire pour la fonction fork */
#include <unistd.h> /* necessaire pour la fonction fork */
#include <stdio.h> /* necessaire pour la fonction perror */

int main() {
	pid_t pid;
	if ((pid = fork()) < 0)
		perror("fork error");
	else if (pid == 0) 
	{
		if (execl("/home/reyesamaro-a/Documents/DepInfo/SO/TP5-6/affichez.exe","affichez.exe","salut", (char *) 0) < 0)
			perror("execl error");
	}
	return 0;
}