#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

int main(void)
{
	int pid = fork();
	if(pid == -1) return 1;
	if(pid == 0)
	{
		while (1)
		{
			printf("Some text goes here\n");
			usleep(50000);
		}
	}
	else{
		kill(pid,SIGSTOP);
		sleep(1);
		kill(pid, SIGCONT); //
		sleep(1);
		kill(pid, )
		wait(NULL);
	}
	return 0;
}