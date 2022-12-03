#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int f = fork();

	if(f > 0)
		printf("fork returned positive value. this is the parent of this process: %d the pid of child %d\n", getpid(), f);
	else if(f == 0)
		printf("fork returned 0. this is newly created child process with ID: %d\n", getpid());
	else{
		printf("fork returned negative value , process failed to be created\n");
	}
	printf("========================================================================\n");
}