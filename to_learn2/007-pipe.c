#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void)
{
	int fd[5];
	int fd1 = open("file.txt", O_RDWR);

	if(pipe(fd) == -1){
		printf("error on openning the pipe\n");
		return 1;
	}
	int i = 0;
	while (i < 5)
	{
		printf("-> %d\n", fd[i]);
		i++;
	}	
	
	return 0;
}