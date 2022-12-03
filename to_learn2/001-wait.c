#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	int id = fork();
	int n;
	if (id == 0)
		n = 1;
	else
		n = 6;
	if(id == 0)
		wait();
	int i = n;
	while (i++ < n + 5)
		printf("%d ",i);
	return 0;
}