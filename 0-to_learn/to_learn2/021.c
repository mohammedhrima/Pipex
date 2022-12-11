#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void)
{
	int status;
	char*arg[2];

	arg[0] = "/bin/ls";
	arg[1] = "-l";
	if(fork() == 0)
		execv(arg[0], arg);
	else
		wait(&status);
	return 0;
}