#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int id = fork();
	if (id == 0)
		printf("Hello from child processs\n");
	else
		printf("Hello from main process\n");
	return (0);
}