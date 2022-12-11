#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int status;
	char*arg[2];

	arg[0] = argv[1];
	arg[1] = NULL;
	if(fork() == 0)
		execv(argv[1], arg);
	else
		wait(&status);
	return 0;
}