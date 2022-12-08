#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void)
{
	char buff[4];
	int fd[2];
	if (pipe(fd) < 0)
		return 1;
	char *str = "abcd";
	write(fd[1], str, 4);
	int i = 0;
	char str1[4];
	read(fd[0], str1, 4);
	printf("str1 -> %s\n", str1);

	return 0;
}