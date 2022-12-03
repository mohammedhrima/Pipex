#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int id = fork();
	if( !id)
		fork();
	printf("hey\n");

	return (0);
}