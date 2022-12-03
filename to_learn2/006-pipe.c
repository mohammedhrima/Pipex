#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int fd[3];

	if(pipe(fd + 1) == -1){
		printf("error on openning the pipe\n");
		return 1;
	}
	int id = fork();
	if (id == 0){
		close(fd[1]);
		int x;
		printf("enter chi le3ba: ");
		scanf("%d", &x);
		write(fd[2], &x, sizeof(int));
		close(fd[2]);
	}
	else{
		close(fd[2]);
		int y;
		read(fd[1], &y, sizeof(int));
		close(fd[1]);
		printf("in child process %d\n",y);
	}
	
	return 0;
}