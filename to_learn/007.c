#include <unistd.h>
#include <stdio.h>

int pid1 = -1;
int pid2 = -1;
int pid3 = -1;

int main(void)
{
	pid1 = fork();
	printf("first process pid1=%d ",pid1);
	pid2 = fork();
	printf("second process pid2=%d ",pid2);
	pid3 = fork();
	printf("third process pid3=%d ",pid3);
	printf("current %d", getpid());
	printf("\n================================================\n\n");
	/*if(pid1 == 0)
	{
		printf("first child\n");
		printf("pid3->%d pid2->%d pid1->%d cureent pid->%d\n",pid3,pid2,pid1,getpid());
	}
	if(pid2 == 0)
	{
		printf("second child\n");
		printf("pid3->%d pid2->%d pid1->%d current pid->%d\n",pid3,pid2,pid1,getpid());
	}
	if(pid3 == 0)
	{
		printf("third process\n");
		printf("pid3->%d pid2->%d pid1->%d current pid->%d\n",pid3,pid2,pid1,getpid());
	}*/

}