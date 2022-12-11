#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int fd[2];

	if(pipe(fd) == -1){
		printf("error on openning the pipe\n");
		return 1;
	}
	int id = fork();
	if (id == 0){
		close(fd[0]);
		int x;
		printf("enter chi le3ba: ");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
	}
	else{
		close(fd[1]);
		int y;
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("in child process %d\n",y);
	}
	
	return 0;
}