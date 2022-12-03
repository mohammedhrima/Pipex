#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	if (!fork())
	{
		printf("I'm a child\n");
		execlp("ls","ls","-al",NULL);
		printf("after execlp");
	}
	else
		printf("I'm parent %d\n",getpid());

	return (0);
}