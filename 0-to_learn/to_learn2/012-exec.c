#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void)
{
	int pid = fork();
	if(pid == -1){
		return 1;
	}
	if(pid == 0)
	{
		//child process
		int file = open("output", O_RDWR | O_CREAT, 0777);
		if (file == -1)
			return 2;
		printf("The fd to ping results: %d\n",file);	
		/*int file2 = */dup2(file, STDOUT_FILENO);
		//printf("The duplicated fd: %d\n",file2);	
		close(file);

		int err = execlp("ping","ping", "-c", "3" ,"google.com", NULL);
		if(err == -1)
		{
			printf("Could not find program to execute\n");
			return 2;
		}
	}else{
		//parent process
		int wstatus;
		wait(&wstatus);
		if(WIFEXITED(wstatus))
		{
			int statusCode = WEXITSTATUS(wstatus);
			if(statusCode == 0) printf("Success\n");
			else printf("Failure wth status code %d\n",statusCode);
		}
		printf("Some new process ");
	}
	return 0;
}