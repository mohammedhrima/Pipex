#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int id = fork();
	int id1 = fork();
	printf("current id: %d , fork: %d\n", getpid(), id);
	int res = wait(NULL);
	if(res == -1) printf("no children to wait\n");
	else printf("%d finished execution\n", res);
	return (0);
}