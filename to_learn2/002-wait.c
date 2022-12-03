#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	pid_t q;
	pid_t p;
	printf("before fork\n");
	p = getpid();
	q = fork();
	if(q == 0)
	{
		printf("this is child with id:%d\n",getpid());
		printf("my parent id:%d\n", p);
	}
	else
	{
		//wait(NULL);
		printf("this is parent with id:%d\n", getpid());
		printf("my child id:%d\n",q);
	}
	printf("Common\n");
	return 0;
}