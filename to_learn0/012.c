#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
	pid_t p1 = fork();
	if(!p1)
	{
		printf("Child P1 -> %d\n", getpid());
		sleep(10);
		printf("Exit P1\n");
		return(0);
	}

	pid_t p2 = fork();
	if(!p2)
	{
		printf("Child P2 -> %d\n", getpid());
		sleep(5);
		printf("Exit P2\n");
		return(0);
	}

	pid_t w_pid1 = wait(NULL);
	pid_t w_pid2 = wait(NULL);
	if(w_pid1 == -1 || w_pid2 == -1)
	{
		printf("exist 1");
		exit(0);
	}
	if(w_pid1 > 0)
		printf("w_pid1 = %d\n", w_pid1);
	if(w_pid2 > 0)
		printf("w_pid2 = %d\n", w_pid2);
}