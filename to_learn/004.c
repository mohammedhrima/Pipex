#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	if (!fork())
	{
		printf("child");
		printf("Hello World %d\n", getpid());
	}
	else
		printf("parent");

	return (0);
}