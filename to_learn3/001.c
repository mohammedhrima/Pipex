#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	int res = 0;
	int pid = fork();
	if (pid == 0)
	{
		res = -1;
		return -1;
	}
	else
	{
		int ret = wait(NULL);
		printf("%d\n",res);
	}
	
}