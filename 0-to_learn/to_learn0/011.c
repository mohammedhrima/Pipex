#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
int main(void)
{
	int id = fork();
	int n;
	if(!id)
	{
		//we are in vhild process
		n = 1;
	}
	else {
		//we are in main process
		n = 6;
	}
	if (id)
		wait();
	
	for (int i = n; i < n + 5; i++)
	{
		printf("%d ", i);
		fflush(stdout);
	}
	printf("\n");

	return (0);
}