#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/signal.h>

void erreur(char *s);
void suite(int n){};

int main(int argc, char ** argv)
{
	int temp, fd0, fd1, fd2, pid;
	if((fd0 = open("/dev/null", O_RDONLY)) == -1) erreur("Ouverture fichier null");
	if((fd1 = open("nohup.out", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1 ) erreur("Ouverture fichier nohup.out");
	if((fd2 = open("nohup.err", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1 ) erreur("Ouverture fichier nohup.err");

	pid = fork();

	if(pid == 0)
	{
		signal(SIGHUP, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);

		close(0); dup(fd0);
		close(1); dup(fd1);
		close(2); dup(fd2);

		temp = atoi(argv[1]);

		signal(SIGALRM, suite);
		alarm(temp);
		pause();
		execvp(argv[2], argv + 2);
		erreur("Le programme n'a pas fonctionné correctement");
		exit(-1);
	}
	printf("PID fils : %d\n", pid);
}
void erreur(char *s)
{
	perror(s);
	exit(-2);
}
